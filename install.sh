#!/bin/bash

# Останавливаемся если любая команда завершилась с ошибкой
set -e

echo "=== Calculator Installation ==="

# --- Сборка ---
echo "[1/4] Configuring..."
cmake -B build -DCMAKE_BUILD_TYPE=Release

echo "[2/4] Building..."
cmake --build build -j$(nproc)

echo "[3/4] Installing binary..."
sudo cmake --install build

# --- Установка службы ---
echo "[4/4] Installing systemd service..."
sudo cp systemd/calculator.service /etc/systemd/system/calculator.service

echo ""
echo "=== Done! ==="
echo ""
echo "Run the following commands to start the service:"
echo ""
echo "  sudo systemctl daemon-reload"
echo "  sudo systemctl enable calculator"
echo "  sudo systemctl start calculator"
echo ""
echo "Check status:"
echo "  sudo systemctl status calculator"