# Bare-Metal Preemptive Task Scheduler | STM32F446RE

A fully custom, bare-metal task scheduler written in C for the STM32F446RE (ARM Cortex-M4) microcontroller. 

This project completely bypasses the STM's Hardware Abstraction Layer (HAL). It is built from the ground up to demonstrate a deep understanding of the ARMv7E-M architecture, the GCC cross-compilation toolchain, memory mapping, and hardware-level context switching and so on.

## ⚙️ Architecture - bascially how it works!

This project guides through how a boot sequence within a uP takes place, what tasks/process takes place to flash a program onto a Microprocessor.

* **Custom Startup File:** It manually defines the ARM Vector Table, implements the `Reset_Handler`, initializes the `.data` and `.bss` sections in SRAM, and safely branches to `main()`.
* **Custom Linker Script (`.ld`):** The ARM core doesn't inherently know where ST's Flash or SRAM is physically located. This custom linker script manually maps the compiled object files (`*.o`), placing instructions (`.text`) and constants (`.rodata`) into Flash memory, while routing variables (`.data`, `.bss`) to SRAM. 
* **Automated Makefile:** Manages the `arm-none-eabi-gcc` toolchain, automating the compilation, assembly, and linking stages to generate the final Executable and Linkable Format (`.elf`) file.
* **The SysTick Timer:** Utilizes the Cortex-M4's internal 24-bit down-counter to generate a precise 1-millisecond hardware heartbeat, which orchestrates the context switching between user tasks.
* **Naked Assembly & PendSV:** Uses pure inline assembly and the `__attribute__((naked))` directive to manually manipulate the CPU's Stack Pointers (MSP and PSP) and push/pop core registers (`R0-R11`, `LR`) to safely swap task contexts.

## Hardware Requirements & Wiring

* **Microcontroller:** STM32 Nucleo-F446RE Board.
* **External Hardware:** 4x LEDs.
* **Interfacing:** Connected to GPIO pins **PA9, PA10, PA11, and PA12**.

> **Note on Hardware Protection:** Do not wire the LEDs directly to the STM32 GPIO pins, as the current draw can permanently damage the silicon. You **must** wire a current-limiting resistor (160Ω to 390Ω) in series with each LED to safely test the scheduler.

## 🛠️ Software Dependencies - tools!

To build, flash, and debug this project, you need the following host-machine tools:
* **Make:** For build automation.
* **ARM GCC Toolchain:** (`arm-none-eabi`) for cross-compiling.
* **OpenOCD:** To bridge the communication between the host PC and the STM32's onboard ST-Link debug port.
* **PuTTY (or any Telnet client):** To emulate the client-server telnet protocol for flashing commands and viewing Semihosting `printf` output.
* **GDB Toolchain:** Alternatively, you can use `arm-none-eabi-gdb` for full step-through debugging. Once OpenOCD is running, open a new terminal 
> **Note:** When using GDB, you must prefix OpenOCD hardware commands with `monitor` (e.g., `monitor reset init` or `monitor arm semihosting enable`). Standard debugging commands like `break`, `step`, and `continue` are used normally without the prefix, connect and use monitor for every commands afterwards )

## Build and Flash the final.elf
### 1. Compile the Source Code
Open your primary terminal in the project directory and run:
```bash
make all
```
*This invokes the toolchain to compile the `.c` files into `.o` objects, links them according to the `.ld` script, and generates the final `.elf` binary.*

### 2. Start the OpenOCD Server
In the same terminal, establish the connection to the microcontroller:
```bash
make load
```
*(Ensure your specific board's `.cfg` file is properly targeted in the Makefile).*

### 3. Flash & Debug via Telnet
OpenOCD uses GDB to debug the microprocessor via a client-server protocol. Leave the first terminal running, open **PuTTY**, and configure it as follows:
* **Host Name:** `localhost`
* **Port:** `4444`
* **Connection Type:** `Telnet`

Once the PuTTY terminal opens, execute the following commands to halt the CPU, flash the `.elf` file, enable the debug output, and restart the chip:

```bash
> reset init
> flash write_image erase <your_file_name.elf>
> arm semihosting enable
> reset
```

### 4. Monitor the Output
Because this project utilizes ARM Semihosting, the standard `printf` statements from the individual task handlers will be routed through the ST-Link and displayed directly in your OpenOCD terminal session, allowing you to watch the preemptive scheduler switch contexts in real-time!

---
Feel free to drop a ⭐ for this repo!
