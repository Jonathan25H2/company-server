#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"
CYAN="\033[1;36m"
BOLD="\033[1m"
RESET="\033[0m"

pause() {
    echo
    read -p "Press ENTER to return..."
}

while true; do
    clear

    HOST=$(hostname)
    IP=$(hostname -I | awk '{print $1}')
    UPTIME=$(uptime -p | sed 's/up //')
    RAM=$(free -h | awk '/Mem:/ {print $3 " / " $2}')
    DISK=$(df -h / | awk 'NR==2 {print $3 " / " $2 " (" $5 ")"}')
    LOAD=$(awk '{print $1}' /proc/loadavg)

    if ping -c 1 -W 1 1.1.1.1 >/dev/null 2>&1; then
        NETWORK="${GREEN}✓ Connected${RESET}"
    else
        NETWORK="${RED}✗ Offline${RESET}"
    fi

    FAILED=$(systemctl --failed --no-legend 2>/dev/null | wc -l)

    if [ "$FAILED" -eq 0 ]; then
        HEALTH="${GREEN}✓ HEALTHY${RESET}"
    else
        HEALTH="${RED}⚠ $FAILED FAILED SERVICE(S)${RESET}"
    fi

    echo -e "${CYAN}====================================================${RESET}"
    echo -e "${BOLD}                    SLAN SERVER${RESET}"
    echo -e "${CYAN}====================================================${RESET}"
    echo
    echo -e " System Health:   $HEALTH"
    echo
    echo -e " Hostname:        $HOST"
    echo -e " IP Address:      $IP"
    echo -e " Uptime:          $UPTIME"
    echo
    echo -e " CPU Load:        $LOAD"
    echo -e " Memory:          $RAM"
    echo -e " Storage:         $DISK"
    echo -e " Network:         $NETWORK"
    echo
    echo "----------------------------------------------------"
    echo "  1) Dashboard"
    echo "  2) Storage"
    echo "  3) Users"
    echo "  4) Network"
    echo "  5) Services"
    echo "  6) Backup"
    echo "  7) Updates"
    echo "  8) Advanced Terminal"
    echo "  0) Power"
    echo "----------------------------------------------------"
    echo

    read -p " Select option: " choice

    case "$choice" in

        1)
            clear
            echo "=== SYSTEM DASHBOARD ==="
            echo
            uptime
            echo
            free -h
            echo
            df -h /
            pause
            ;;

        2)
            clear
            echo "=== STORAGE ==="
            echo
            lsblk
            echo
            df -h
            pause
            ;;

        3)
            clear
            echo "=== USERS ==="
            echo
            awk -F: '$3 >= 1000 {print $1}' /etc/passwd
            pause
            ;;

        4)
            clear
            echo "=== NETWORK ==="
            echo
            ip -br addr
            echo
            ip route
            pause
            ;;

        5)
            clear
            echo "=== FAILED SERVICES ==="
            echo
            systemctl --failed
            pause
            ;;

        6)
            clear
            echo "=== BACKUP ==="
            echo
            echo "Backup system not configured yet."
            pause
            ;;

        7)
            clear
            echo "=== SYSTEM UPDATE ==="
            echo
            apt update
            apt upgrade
            pause
            ;;

        8)
            clear
            echo -e "${YELLOW}ADVANCED MODE${RESET}"
            echo "Type 'exit' to return to SLAN."
            echo
            bash
            ;;

        0)
            clear
            echo "=== POWER ==="
            echo
            echo " 1) Restart server"
            echo " 2) Shutdown server"
            echo " 0) Cancel"
            echo
            read -p " Select option: " power

            case "$power" in
                1)
                    echo "Restarting..."
                    reboot
                    ;;
                2)
                    echo "Shutting down..."
                    poweroff
                    ;;
            esac
            ;;

    esac
done
