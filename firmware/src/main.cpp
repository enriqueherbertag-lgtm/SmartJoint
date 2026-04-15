/**
 * SmartJoint - Firmware para STM32F405
 * 
 * Modos de control: Posición, Velocidad, Par, Seguro.
 * Comunicación: UART a 1 Mbps (protocolo de paquetes).
 * Sensor: AS5715R (inductivo, 360° absoluto).
 * Driver: DRV8320 (Puente H de 48V, 10A).
 * 
 * Autor: Enrique Aguayo H.
 * Licencia: Copyright © 2026 Enrique Aguayo. Todos los derechos reservados.
 */

#include "main.h"
#include "pid.h"
#include "as5715r.h"
#include "drv8320.h"
#include "uart_protocol.h"

// ----------------------------
// Constantes y parámetros
// ----------------------------
#define CONTROL_FREQ_HZ     1000        // Frecuencia del bucle de control (1 kHz)
#define CONTROL_PERIOD_US   (1000000 / CONTROL_FREQ_HZ)

#define WATCHDOG_TIMEOUT_MS 100         // Si no hay comando en 100 ms, entra en modo seguro

// Modos de control
typedef enum {
    MODE_IDLE = 0,      // Motor desactivado
    MODE_POSITION,      // Control de posición (grados)
    MODE_VELOCITY,      // Control de velocidad (grados/segundo)
    MODE_TORQUE,        // Control de par (Nm)
    MODE_SAFE           // Modo seguro (fallo de enlace)
} control_mode_t;

// Parámetros del PID (posición)
PID_HandleTypeDef pid_pos;
float pid_pos_kp = 10.0f;
float pid_pos_ki = 0.5f;
float pid_pos_kd = 1.0f;

// Parámetros del PID (velocidad)
PID_HandleTypeDef pid_vel;
float pid_vel_kp = 5.0f;
float pid_vel_ki = 0.2f;
float pid_vel_kd = 0.5f;

// Parámetros del PID (par)
PID_HandleTypeDef pid_torque;
float pid_torque_kp = 2.0f;
float pid_torque_ki = 0.1f;
float pid_torque_kd = 0.2f;

// Estado de la articulación
volatile control_mode_t current_mode = MODE_IDLE;
volatile float target_value = 0.0f;      // Objetivo (grados, grados/s, o Nm)
volatile float current_position = 0.0f;   // Posición actual (grados)
volatile float current_velocity = 0.0f;   // Velocidad actual (grados/s)
volatile float current_torque = 0.0f;     // Par actual (Nm)
volatile float motor_output = 0.0f;       // Salida al motor (0-1, duty cycle)

volatile uint32_t last_command_time = 0;  // Timestamp del último comando recibido

// ----------------------------
// Inicialización
// ----------------------------
void SystemClock_Config(void) {
    // Configuración del reloj a 168 MHz (típico para STM32F405)
    // (Código generado por CubeMX - se omite por brevedad)
}

void GPIO_Init(void) {
    // Configuración de pines: LED de estado, enable del driver, etc.
}

void UART_Init(void) {
    // Configurar UART a 1 Mbps, 8N1
    // (Código generado por CubeMX - se omite por brevedad)
}

void TIM_Init(void) {
    // Configurar timer para interrupción a 1 kHz (bucle de control)
    // (Código generado por CubeMX - se omite por brevedad)
}

void AS5715R_Init(void) {
    // Inicializar comunicación SPI con el sensor AS5715R
    as5715r_init();
    // Leer posición inicial
    current_position = as5715r_get_angle();
}

void DRV8320_Init(void) {
    // Inicializar driver de motor (PWM, enable, etc.)
    drv8320_init();
    drv8320_enable(true);
    drv8320_set_duty(0.0f);  // Arranca con motor parado
}

void PID_Init(void) {
    // Inicializar PID de posición
    PID_Init(&pid_pos, pid_pos_kp, pid_pos_ki, pid_pos_kd, CONTROL_FREQ_HZ);
    PID_SetOutputLimits(&pid_pos, -1.0f, 1.0f);  // Salida limitada a duty cycle
    PID_SetIntegralLimits(&pid_pos, -0.5f, 0.5f);

    // Inicializar PID de velocidad
    PID_Init(&pid_vel, pid_vel_kp, pid_vel_ki, pid_vel_kd, CONTROL_FREQ_HZ);
    PID_SetOutputLimits(&pid_vel, -1.0f, 1.0f);
    PID_SetIntegralLimits(&pid_vel, -0.5f, 0.5f);

    // Inicializar PID de par
    PID_Init(&pid_torque, pid_torque_kp, pid_torque_ki, pid_torque_kd, CONTROL_FREQ_HZ);
    PID_SetOutputLimits(&pid_torque, -1.0f, 1.0f);
    PID_SetIntegralLimits(&pid_torque, -0.5f, 0.5f);
}

// ----------------------------
// Bucle de control (se ejecuta a 1 kHz)
// ----------------------------
void ControlLoop(void) {
    // 1. Leer sensores
    current_position = as5715r_get_angle();
    current_velocity = as5715r_get_velocity();  // Pendiente: implementar
    current_torque = drv8320_get_current();      // Pendiente: implementar

    // 2. Verificar watchdog (fallo de enlace)
    uint32_t now = HAL_GetTick();
    if ((now - last_command_time) > WATCHDOG_TIMEOUT_MS) {
        if (current_mode != MODE_SAFE) {
            current_mode = MODE_SAFE;
        }
    }

    // 3. Control según el modo
    float output = 0.0f;

    switch (current_mode) {
        case MODE_IDLE:
            output = 0.0f;
            break;

        case MODE_POSITION:
            output = PID_Update(&pid_pos, target_value, current_position);
            break;

        case MODE_VELOCITY:
            output = PID_Update(&pid_vel, target_value, current_velocity);
            break;

        case MODE_TORQUE:
            output = PID_Update(&pid_torque, target_value, current_torque);
            break;

        case MODE_SAFE:
            // Modo seguro: mantiene posición actual con par reducido
            output = PID_Update(&pid_pos, current_position, current_position);
            output = output * 0.5f;  // 50% de par
            break;
    }

    // 4. Limitar salida y aplicar al motor
    if (output > 1.0f) output = 1.0f;
    if (output < -1.0f) output = -1.0f;
    motor_output = output;
    drv8320_set_duty(motor_output);

    // 5. Enviar telemetría (opcional, cada 10 ms)
    static uint32_t last_telemetry = 0;
    if ((now - last_telemetry) >= 10) {
        uart_send_telemetry(current_mode, current_position, current_velocity, current_torque, motor_output);
        last_telemetry = now;
    }
}

// ----------------------------
// Interrupción del timer (1 kHz)
// ----------------------------
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    ControlLoop();
}

// ----------------------------
// Procesamiento de comandos UART
// ----------------------------
void ProcessCommand(uint8_t *buffer, uint8_t len) {
    // Formato del paquete: [ID][MODE][TARGET_H][TARGET_L][CHECKSUM]
    // ID = 0x01 (para SmartJoint)
    // MODE: 0=IDLE, 1=POSITION, 2=VELOCITY, 3=TORQUE, 4=SAFE
    // TARGET: float de 32 bits en little-endian
    // CHECKSUM: XOR de todos los bytes

    if (len != 8) return;

    uint8_t id = buffer[0];
    uint8_t mode = buffer[1];
    float target = *(float*)(buffer + 2);
    uint8_t checksum = buffer[6];

    // Verificar checksum
    uint8_t calc = 0;
    for (int i = 0; i < 6; i++) calc ^= buffer[i];
    if (calc != checksum) return;

    // Actualizar estado
    last_command_time = HAL_GetTick();
    target_value = target;

    switch (mode) {
        case 0: current_mode = MODE_IDLE; break;
        case 1: current_mode = MODE_POSITION; break;
        case 2: current_mode = MODE_VELOCITY; break;
        case 3: current_mode = MODE_TORQUE; break;
        case 4: current_mode = MODE_SAFE; break;
        default: return;
    }

    // Resetear PID cuando cambia el modo o el objetivo
    if (current_mode == MODE_POSITION) PID_Reset(&pid_pos);
    if (current_mode == MODE_VELOCITY) PID_Reset(&pid_vel);
    if (current_mode == MODE_TORQUE) PID_Reset(&pid_torque);
}

// ----------------------------
// main
// ----------------------------
int main(void) {
    // Inicialización del hardware
    HAL_Init();
    SystemClock_Config();
    GPIO_Init();
    UART_Init();
    TIM_Init();
    AS5715R_Init();
    DRV8320_Init();
    PID_Init();

    // Bucle principal (solo procesa comandos UART)
    while (1) {
        uint8_t buffer[8];
        if (uart_receive_packet(buffer, 8, 10)) {  // timeout 10 ms
            ProcessCommand(buffer, 8);
        }
        // El control real se ejecuta en la interrupción del timer
    }
}
