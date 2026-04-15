[![Licencia](https://img.shields.io/badge/Licencia-Copyright%20%28c%29%202026%20Enrique%20Aguayo-red)](LICENSE)
[![Estado](https://img.shields.io/badge/Estado-Hip%C3%B3tesis%20en%20desarrollo-yellow)](https://github.com/enriqueherbertag-lgtm/SmartJoint)
[![Documentación](https://img.shields.io/badge/Documentación-SmartJoint-blue)](./docs/)
[![Asistencia IA](https://img.shields.io/badge/Asistencia%20IA-DeepSeek-brightgreen)](https://deepseek.com)

# SmartJoint: Articulación inteligente de accionamiento directo

**Módulo autónomo para robótica, prótesis y exoesqueletos. Integra motor, sensor absoluto, controlador local y comunicación de alta velocidad.**

SmartJoint no es un motor genérico. Es un sistema completo que incluye:

- Motor de accionamiento directo (sin engranajes, sin backlash).
- Sensor de posición inductivo AS5715R (360° absoluto, <0.075°).
- Controlador local STM32F405 con PID.
- Driver de potencia (48V, 10A).
- Comunicación por fibra óptica (bus serie a 1 Mbps).
- Refrigeración líquida opcional.

No depende de un controlador externo. Cada articulación es inteligente.

---

## ¿Qué problema resuelve?

Las articulaciones robóticas actuales son torpes, caras o difíciles de integrar:

- Los servomotores con engranajes tienen backlash (holgura) y se desgastan.
- Los motores paso a paso pierden pasos si hay carga.
- Los actuadores lineales son lentos y ruidosos.
- Los sistemas industriales son cerrados y caros (miles de dólares por articulación).

SmartJoint es abierto, modular y de bajo costo. Un ingeniero con una impresora 3D y conocimientos de electrónica puede construir una prótesis de brazo con 4 articulaciones por menos de 500 USD.

---

## Especificaciones técnicas

| Parámetro | Valor |
|---|---|
| Diámetro | 60 mm |
| Longitud | 80 mm |
| Peso | 400-500 g |
| Par máximo | 50 Nm (pico), 20 Nm (continuo) |
| Velocidad máxima | 300 rpm |
| Alimentación | 48V DC |
| Consumo en reposo | 5 W |
| Consumo en movimiento | 50-200 W |
| Precisión de posición | ±0.1 grados |
| Resolución del sensor | <0.075 grados |
| Rango del sensor | 360° absoluto |
| Comunicación | UART sobre fibra óptica o RS-485 |
| Frecuencia de control | 1 kHz |
| Refrigeración | Líquida (opcional, hasta 50 W disipados) |

---

## Modos de control

- **Modo posición:** Se mueve hasta el ángulo indicado (en grados).
- **Modo velocidad:** Gira a la velocidad angular indicada (grados/segundo).
- **Modo par:** Aplica el par indicado (Nm) al eje.
- **Modo seguro (fallo de enlace):** Configurable por hardware. Puede ser "retención" (mantiene la posición con par reducido) o "libre" (desactiva el motor).

---

## Componentes (lista de materiales)

| Componente | Modelo | Costo (USD) |
|---|---|---|
| Estator y rotor mecanizados | Diseño propio (fabricación externa) | 20-30 |
| Imanes de neodimio N52 | Varios (ej. SuperMagnetMan) | 10-15 |
| Bobinas de cobre | Hilo AWG 24 | 5-10 |
| Sensor inductivo | AS5715R (ams AG) | 12-15 |
| Rueda fónica conductora | Aluminio o cobre mecanizado | 5-10 |
| Microcontrolador | STM32F405 (o similar) | 10-15 |
| Driver de motor | DRV8320 (Texas Instruments) | 8-12 |
| Reguladores de voltaje | 48V -> 5V -> 3.3V | 5-10 |
| PCB controladora | Diseño propio (JLCPCB) | 10-15 |
| Transceptor SFP (opcional) | TP-Link TL-SM311LS | 25-30 |
| Conectores y cables | Varios | 10-15 |
| **Total (aproximado)** | | **120-180 USD** |

En volumen (>100 unidades), el costo puede bajar a 60-100 USD por articulación.

---

## Estado del proyecto

- [x] Concepto definido.
- [x] Especificaciones técnicas completas.
- [x] Componentes seleccionados.
- [ ] Diseño mecánico (planos STEP/STL) (pendiente).
- [ ] Esquema electrónico (KiCad) (pendiente).
- [ ] PCB controladora (pendiente).
- [ ] Firmware (C++ para STM32) (pendiente).
- [ ] Prototipo funcional (pendiente).
- [ ] Pruebas de par, velocidad y disipación térmica (pendiente).

---

## Estructura del repositorio

- `docs/` - Documentación técnica (especificaciones, guías).
- `hardware/` - Planos mecánicos (STEP/STL) y esquemas electrónicos (KiCad).
- `firmware/` - Código fuente para el STM32.
- `software/` - Ejemplos de control (Python, C++).
- `LICENSE` - Copyright (uso no comercial permitido, comercial requiere licencia).

---

## Cómo contribuir

Este es un proyecto abierto (en cuanto a documentación, no en cuanto a licencia comercial). Puedes:

- Abrir un issue para reportar errores en la especificación.
- Proponer mejoras (componentes alternativos, cambios de diseño).
- Compartir tus propios diseños de planos o firmware (bajo la misma licencia).

No se aceptan contribuciones comerciales sin autorización expresa del autor.

---

## Autor

**Enrique Aguayo H.** – Mackiber Labs  
Contacto: eaguayo@migst.cl  
ORCID: 0009-0004-4615-6825  
GitHub: @enriqueherbertag-lgtm

*Documentación asistida por DeepSeek (IA) en redacción y estructura.*

---

## Licencia

Copyright © 2026 Enrique Aguayo. Todos los derechos reservados.

**Permitido:** Uso no comercial con fines educativos o de investigación. Distribución sin modificación con atribución.

**Prohibido sin autorización expresa:** Uso comercial, modificación para entornos de producción, distribución de versiones modificadas.

Para licencias comerciales: eaguayo@migst.cl
