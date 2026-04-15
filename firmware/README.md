# Firmware de SmartJoint

Esta carpeta contiene el código fuente para el microcontrolador STM32F405.

## Contenido esperado

- `src/` - Código fuente (C++).
- `inc/` - Archivos de cabecera.
- `lib/` - Bibliotecas externas (CMSIS, STM32 HAL, etc.).
- `platformio.ini` - Configuración para PlatformIO.
- `Makefile` - Para compilación con GCC.

## Estado

- [ ] Código base (bucle principal, inicialización) (pendiente).
- [ ] Controlador PID (pendiente).
- [ ] Driver del motor (PWM, corriente) (pendiente).
- [ ] Protocolo de comunicación (pendiente).
- [ ] Modos de control (posición, velocidad, par) (pendiente).

## Nota

El firmware no está disponible todavía. Se publicará cuando se complete el prototipo funcional. Mientras tanto, puedes consultar la especificación de modos de control en `docs/SmartJoint_Specification.md` para implementar tu propio firmware.
