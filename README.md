# Calculator

## Description
Simple console calculator for UNIX
## How to install
- Clone repository
`git clone https://github.com/Vaturia/calculator.git`
- Install
```bash
chmod +x install.sh
sudo ./install.sh
```
## How use
`systemctl start calculator`

- Uninstall
chmod +x uninstall.sh
sudo ./uninstall.s
## Tests
`./build/tests/run_tests`
## Check ThreadSanitizer
- build with sanitazer
```
cmake -B build-tsan -DENABLE_TSAN=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-tsan -j$(nproc)
```
- Run with sanitazer
`TSAN_OPTIONS="suppressions=tsan_suppressions.txt" ./build-tsan/calculator`
- Test cases for sanitzer
```bash
chmod +x test_san.sh
./test_san.sh
```