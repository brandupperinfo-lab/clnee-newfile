# CLAUDE.md - AI Assistant Guide for Ecoit-USCUV-G030F6

## Project Overview

This is an **STM32G030F6** embedded firmware project implementing a USB HID device controller. The project appears to be designed for arcade/game controller interfacing with support for:
- NKRO (N-Key Rollover) keyboard functionality
- KONAMI-style joystick emulation
- Custom input processing through the ACIO (Arcade Controller Input/Output) library

**Project Name**: Ecoit-USCUV-G030F6
**Target MCU**: STM32G030F6Px (ARM Cortex-M0+)
**Flash**: 32 KB
**RAM**: 8 KB
**IDE**: STM32CubeIDE
**Build System**: Eclipse-managed Make (arm-none-eabi-gcc)

---

## Hardware Specifications

### Microcontroller Details
- **MCU**: STM32G030F6Px
- **Core**: ARM Cortex-M0+ @ 16 MHz (configurable up to 64 MHz)
- **Package**: TSSOP20
- **Architecture**: 32-bit RISC

### Peripherals in Use
Based on the codebase, the following peripherals are utilized:
- **ADC1**: Analog-to-digital conversion (5 channels, includes temperature sensing)
- **DMA**: Direct Memory Access for efficient data transfer
- **TIM (Timers)**: Timing and PWM generation
- **GPIO**: General purpose I/O for button inputs
- **USB**: USB 2.0 Full-Speed device (HID class)

---

## Codebase Structure

```
.
├── ACIO/                          # Custom ACIO library
│   └── src/
│       ├── ACIO.h                 # Main ACIO header (includes all modules)
│       ├── core/
│       │   ├── common/
│       │   │   ├── null.h         # NULL state definitions
│       │   │   └── state.h        # State machine utilities
│       │   └── input/
│       │       ├── EdgeInputController.c/h    # Edge-triggered input handling
│       │       ├── NthInputController.c/h     # Nth-press detection
│       │       ├── InputState.h               # Input state definitions
│       │       └── LogicInput.h               # Logical input abstraction
│       └── utility/
│           ├── hid_descriptor.h   # USB HID descriptor definitions
│           ├── keycode.h          # Keyboard keycode mappings
│           └── usb_report.c/h     # USB report generation (NKRO, Joystick)
│
├── Core/                          # Main application code
│   ├── Inc/                       # Header files
│   │   ├── main.h
│   │   ├── acio_driver.h          # ACIO integration layer
│   │   ├── task.h                 # Task scheduling
│   │   ├── bsp.h                  # Board Support Package
│   │   ├── adc.h, dma.h, gpio.h, tim.h
│   │   ├── stm32g0xx_hal_conf.h   # HAL configuration
│   │   └── stm32g0xx_it.h         # Interrupt handlers
│   ├── Src/                       # Source files
│   │   ├── main.c                 # Application entry point
│   │   ├── acio_driver.c          # ACIO driver implementation
│   │   ├── task.c                 # Task implementation
│   │   ├── bsp.c                  # Board-specific code
│   │   ├── adc.c, dma.c, gpio.c, tim.c
│   │   ├── stm32g0xx_hal_msp.c    # HAL MSP initialization
│   │   ├── stm32g0xx_it.c         # Interrupt service routines
│   │   ├── syscalls.c, sysmem.c   # System calls/memory
│   │   └── system_stm32g0xx.c     # System initialization
│   └── Startup/
│       └── startup_stm32g030f6px.s  # Startup assembly code
│
├── Drivers/                       # STM32 HAL/CMSIS drivers
│   ├── STM32G0xx_HAL_Driver/      # Hardware Abstraction Layer
│   └── CMSIS/                     # Cortex Microcontroller Software Interface Standard
│
├── Debug/                         # Build output directory (DO NOT EDIT)
├── .cproject                      # Eclipse CDT project configuration
├── .project                       # Eclipse project file
├── .mxproject                     # STM32CubeMX project metadata
├── Ecoit-USCUV-G030F6.ioc         # STM32CubeMX configuration (graphical)
└── STM32G030F6PX_FLASH.ld         # Linker script
```

### Module Responsibilities

#### ACIO Library
Custom library for handling arcade controller inputs with sophisticated features:
- **EdgeInputController**: Detects rising/falling edges on inputs
- **NthInputController**: Handles multi-press detection (double-click, triple-click, etc.)
- **USB Report Generation**: Creates NKRO keyboard and joystick HID reports
- **State Management**: Provides common state machine utilities

#### Core Application
- **main.c**: Entry point, initialization, main loop
- **acio_driver.c**: Integration between ACIO library and hardware
- **task.c**: Task scheduling and management
- **bsp.c**: Board-specific configurations
- **Peripheral drivers**: ADC, DMA, GPIO, TIM initialization

---

## Development Workflow

### 1. Hardware Configuration (STM32CubeMX)
- **Modify**: `Ecoit-USCUV-G030F6.ioc` using STM32CubeMX GUI
- **Regenerates**: Peripheral initialization code in `Core/Src/` and `Core/Inc/`
- **Protected sections**: Code between `/* USER CODE BEGIN */` and `/* USER CODE END */` is preserved

### 2. Application Development
- Add custom logic in `/* USER CODE */` sections
- Implement ACIO callbacks in `acio_driver.c`
- Modify ACIO library as needed in `ACIO/src/`

### 3. Build Process
```bash
# Build in STM32CubeIDE (GUI)
Project → Build Project

# Or use command line (from Debug/ directory)
cd Debug
make clean
make -j$(nproc)
```

**Build Output**: `Debug/Ecoit-USCUV-G030F6.elf` (also generates .hex and .bin)

### 4. Flash and Debug
```bash
# Using STM32CubeIDE
Run → Debug (F11)

# Using st-flash (command line)
st-flash write Debug/Ecoit-USCUV-G030F6.bin 0x8000000

# Using OpenOCD
openocd -f interface/stlink.cfg -f target/stm32g0x.cfg \
  -c "program Debug/Ecoit-USCUV-G030F6.elf verify reset exit"
```

---

## Key Conventions for AI Assistants

### Code Modification Rules

1. **NEVER modify auto-generated code outside USER CODE sections**
   - Files like `adc.c`, `gpio.c`, `tim.c` are auto-generated
   - Only edit code between `/* USER CODE BEGIN */` and `/* USER CODE END */`
   - Exception: Files entirely written by developers (e.g., `task.c`, `acio_driver.c`)

2. **Preserve STM32CubeMX compatibility**
   - Do not remove MX-generated function signatures
   - Do not change peripheral initialization outside USER CODE sections
   - Document any manual changes that conflict with MX regeneration

3. **ACIO library modifications**
   - The `ACIO/` directory is custom code and can be freely modified
   - Maintain consistent naming: `ACIO_` prefix for public APIs
   - Keep header organization: core → common/input, utility → USB/HID

### Coding Style

```c
// Function naming conventions
void ACIO_Public_Function(void);        // Public API (CamelCase with prefix)
static void private_helper(void);       // Private/static (snake_case)

// HAL callbacks (required naming)
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

// Interrupt handlers (required naming)
void TIMx_IRQHandler(void);

// Constants and macros
#define ACIO_MAX_BUTTONS    16          // Uppercase with prefix
#define ADC_CHANNELS        5

// Typedefs
typedef struct {
    uint8_t state;
} ACIO_InputState_TypeDef;              // Suffix with _TypeDef
```

### Memory Constraints

**CRITICAL**: This MCU has only 32 KB Flash and 8 KB RAM

- Avoid large constant arrays in RAM
- Use `const` keyword to place data in Flash
- Minimize stack usage in deeply nested calls
- Check `.map` file in Debug/ directory for memory usage
- If near limits, optimize:
  ```bash
  arm-none-eabi-size Debug/Ecoit-USCUV-G030F6.elf
  ```

### USB HID Considerations

- **Report descriptors** defined in `hid_descriptor.h`
- **NKRO keyboard**: 13-byte array (104 keys max)
- **Joystick**: X/Y axes + 16-button bitfield
- Never send reports faster than 1 ms (USB Full-Speed limitation)

---

## Build Configuration

### Compiler Flags (Debug)
```
-mcpu=cortex-m0plus
-std=gnu11
-g3 -DDEBUG
-DUSE_HAL_DRIVER
-DSTM32G030xx
-Og (optimize for debugging)
```

### Include Paths
```
../Core/Inc
../Drivers/STM32G0xx_HAL_Driver/Inc
../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy
../Drivers/CMSIS/Device/ST/STM32G0xx/Include
../Drivers/CMSIS/Include
../ACIO/src  (implied)
```

### Linker Script
- **File**: `STM32G030F6PX_FLASH.ld`
- **Flash origin**: 0x08000000 (32 KB)
- **RAM origin**: 0x20000000 (8 KB)
- **Stack size**: Check `.ld` file (typically 0x400 / 1 KB)
- **Heap size**: Check `.ld` file (typically 0x200 / 512 bytes)

---

## Common Tasks

### Adding a New Peripheral

1. Open `Ecoit-USCUV-G030F6.ioc` in STM32CubeMX
2. Configure peripheral in graphical interface
3. Generate code (Project → Generate Code)
4. Add user logic in `/* USER CODE */` sections
5. Implement callbacks if needed (e.g., `HAL_UART_RxCpltCallback`)

### Modifying ACIO Functionality

```c
// Example: Add new button callback
// In acio_driver.c
void ACIO_Button_Click_Callback(unsigned char nth) {
    /* USER CODE BEGIN ACIO_Button_Click_Callback */
    switch(nth) {
        case 0:
            // Button 1 clicked
            break;
        case 1:
            // Button 2 clicked
            break;
    }
    /* USER CODE END ACIO_Button_Click_Callback */
}
```

### Adding New USB Report Type

1. Define report structure in `usb_report.h`
2. Implement helper functions in `usb_report.c`
3. Update HID descriptor in `hid_descriptor.h`
4. Integrate with USB middleware (not visible in current codebase)

### Debugging Tips

```c
// Use SWD/SWO for printf debugging (if configured)
printf("ADC value: %d\n", adc_value);

// Use GPIO toggle for timing measurements
HAL_GPIO_TogglePin(DEBUG_GPIO_Port, DEBUG_Pin);

// Use breakpoints in handlers
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    // Set breakpoint here
}

// Check peripheral registers in debugger
// Example: hadc1.Instance->DR (ADC data register)
```

### Memory Analysis

```bash
# View memory usage
arm-none-eabi-size Debug/Ecoit-USCUV-G030F6.elf

# Detailed map file
cat Debug/Ecoit-USCUV-G030F6.map | grep -A 20 "Memory Configuration"

# Section sizes
arm-none-eabi-objdump -h Debug/Ecoit-USCUV-G030F6.elf
```

---

## Testing Strategy

### Unit Testing
- **Not currently implemented** in this project
- Consider using Unity or Ceedling for future tests
- Mock HAL functions for host-based testing

### Hardware Testing
1. Flash firmware to device
2. Connect to USB host (Windows/Linux/Mac)
3. Verify device enumeration: `lsusb` (Linux) or Device Manager (Windows)
4. Test HID reports with tools:
   - Linux: `evtest`, `jstest`
   - Windows: DirectInput testing apps

### ADC Calibration
```c
// Temperature sensor calibration (if used)
// Check Reference Manual for calibration values
#define TEMP110_CAL_ADDR ((uint16_t*) 0x1FFF75CA)
#define TEMP30_CAL_ADDR  ((uint16_t*) 0x1FFF75A8)
```

---

## Important Files Reference

### Configuration Files
- `Ecoit-USCUV-G030F6.ioc`: Hardware configuration (GUI-editable)
- `stm32g0xx_hal_conf.h`: HAL driver configuration
- `STM32G030F6PX_FLASH.ld`: Memory layout and linker settings

### Entry Points
- `main.c:main()`: Application entry
- `startup_stm32g030f6px.s:Reset_Handler`: MCU reset vector
- `stm32g0xx_it.c`: All interrupt handlers

### Critical Callbacks
```c
// In main.c or task.c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);

// In acio_driver.c
void ACIO_Button_Click_Callback(unsigned char nth);
void ACIO_Button_Long_Callback(unsigned char nth, unsigned short iter);
void ACIO_Button_After_Release_Callback(unsigned char nth, unsigned short iter);
```

---

## Git Workflow

### Branch Strategy
- **Main branch**: Stable releases
- **Development branches**: Use `claude/` prefix as required by system
- Feature branches: `feature/<feature-name>`

### Commit Guidelines
```bash
# Example commit messages
git commit -m "Add NKRO support for simultaneous key presses"
git commit -m "Fix ADC DMA buffer overflow in continuous mode"
git commit -m "Update ACIO edge detection timing threshold"
```

### Important: DO NOT Commit
- `Debug/` directory (build artifacts)
- `.DS_Store` files (already present, should be gitignored)
- `*.o`, `*.d`, `*.su`, `*.cyclo` files
- IDE-specific user settings (`.settings/`)

---

## AI Assistant Guidelines

### When Making Changes

1. **Read before modifying**: Always read the complete file before editing
2. **Respect USER CODE sections**: Only modify protected sections in MX files
3. **Test memory impact**: Check if changes fit in 32KB Flash / 8KB RAM
4. **Maintain consistency**: Follow existing naming conventions
5. **Document assumptions**: Comment any hardware-specific assumptions

### When Asked to Add Features

1. **Check memory first**: Estimate Flash/RAM impact
2. **Consider real-time constraints**: This is a USB device (1ms timing critical)
3. **Preserve USB functionality**: Don't break HID report timing
4. **Use ACIO patterns**: Follow existing input controller patterns
5. **Update this document**: If adding major features, update CLAUDE.md

### When Debugging

1. **Check linker map**: Memory overflows are common
2. **Verify interrupt priorities**: HAL uses NVIC priority groups
3. **Test USB timing**: Use USB analyzer if reports are corrupted
4. **Monitor stack usage**: 1KB stack fills quickly with nested calls

### Red Flags to Watch For

- ❌ Modifying auto-generated code outside USER CODE sections
- ❌ Large arrays without `const` keyword
- ❌ Infinite loops without watchdog handling
- ❌ Busy-wait delays in interrupt context
- ❌ Float operations without FPU (Cortex-M0+ lacks FPU)
- ❌ USB reports sent faster than 1ms interval

---

## Resources

### Official Documentation
- [STM32G030 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0454-stm32g0x0-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [STM32G030 Datasheet](https://www.st.com/resource/en/datasheet/stm32g030f6.pdf)
- [STM32CubeIDE User Guide](https://www.st.com/resource/en/user_manual/um2609-stm32cubeide-user-guide-stmicroelectronics.pdf)

### USB HID Resources
- [USB HID Usage Tables](https://www.usb.org/document-library/hid-usage-tables-13)
- [USB Made Simple](http://www.usbmadesimple.co.uk/)

### ARM Cortex-M0+ Resources
- [ARM Cortex-M0+ Technical Reference Manual](https://developer.arm.com/documentation/ddi0484/latest/)

---

## Changelog

**2026-01-08**: Initial CLAUDE.md creation
- Documented project structure and development workflow
- Added AI assistant guidelines for embedded development
- Included memory constraints and USB HID conventions
