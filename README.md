# Pico HID

This library contains the general configuration files for a Pico HID device. The library is based on the [pico-examples](https://github.com/raspberrypi/pico-examples/). The library is intended to be used as a submodule in other projects.

## 🛠️ Setup

### 1. Add the Repository as a Submodule
```bash
git submodule add https://github.com/Danielaca18/repo-template.git
```

### 2. Include the Library
Include the library in your project by adding the following line to your project cmake:
```cmake
add_subdirectory(pico-hid)
target_link_libraries(your_project pico_hidlib)
```

## 💼 License
This project is licensed under the [MIT License](LICENSE), which is a permissive open-source license that allows you to use, modify, and distribute the code for both commercial and non-commercial purposes. You can find the full text of the license in the [LICENSE](LICENSE) file.