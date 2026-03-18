#!/bin/bash

set -e

echo "=== Calculator Uninstallation ==="

# --- Остановка и отключение службы ---
echo "[1/3] Stopping service..."
sudo systemctl stop calculator || true
sudo systemctl disable calculator || true

# --- Удаление файлов ---
echo "[2/3] Removing service file..."
sudo rm -f /etc/systemd/system/calculator.service

echo "[3/3] Removing binary..."
sudo rm -f /usr/local/bin/calculator

# --- Перезагрузка systemd ---
echo "Reloading systemd..."
sudo systemctl daemon-reload

echo ""
echo "=== Done! Calculator has been removed ==="