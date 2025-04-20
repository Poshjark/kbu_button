# "КБУ?" button project

Welcome to the "КБУ?" button project repository! This project is a simple device that allows users to easily initiate the process of obtaining information or remind the team of important questions with the press of a button.

## Table of Contents

- [Description](#description)
- [Installation](#installation)
- [Code Versions](#code-versions)
  - [Classic Approach](#classic-approach)
  - [Hardware Interrupts](#hardware-interrupts)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Description

The "KBU Button?" project implements functionality that allows users to interact with the device through a simple button press. This project can be useful in various scenarios, including workflows, team meetings, and other situations where quick attention is required.

## Installation

1. Download or clone this repository to your computer.
2. Open the project in Arduino IDE.
3. Connect your Arduino board to your computer.
4. Select the appropriate board and port from the "Tools" menu.
5. Upload the code to the board.

## Code Versions

This repository contains two versions of the code:

### Classic Approach

This version is based on the classic microcontroller approach with polling for button state. The code continuously checks if the button is pressed and performs corresponding actions.

**Code Path:** [`classic_version`](https://github.com/Poshjark/kbu_button/tree/main/src/loop_based)

### Hardware Interrupts

This version uses hardware interrupts to handle button presses. This allows for more efficient use of microcontroller resources and real-time event response.

**Code Path:** [`interrupt_version`](https://github.com/Poshjark/kbu_button/tree/main/src/interrupt_based)

## Usage

After uploading the code to the board, you can use the button as follows:

1. Raise your hand and clench it into a fist.
2. Press the button.
3. A message "KBU?" will appear on your device screen, initiating the process of obtaining information.

## Contributing

If you would like to contribute to this project, please fork the repository and submit a pull request with your changes. We welcome any improvements and ideas!

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Thank you for your interest in the "KBU Button?" project! If you have any questions or suggestions, feel free to reach out!
