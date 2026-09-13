#!/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"
CYAN="\033[1;36m"
BOLD="\033[1m"
RESET="\033[0m"

DISK_CACHE=""
LAST_DISK_UPDATE=0

pause_menu() {
    echo
    read -p "Press ENTER to return..."
}

get_disk() {
    local now
    now=$(date +%s)

    if [ -z "$DISK_CACHE" ] || [ $((now - LAST_DISK_UPDATE)) -ge 120 ]; then
        DISK_CACHE=$(df -h / | awk 'NR==2 {print $3 " / " $2 " (" $5 ")"}')
        LAST_DISK_UPDATE=$now
    fi
}

get_cpu_usage() {
    read -r cpu user nice system idle iowait irq softirq steal guest guest_nice < /proc/stat

    local idle1=$((idle + iowait))
    local nonidle1=$((user + nice + system + irq + softirq + steal))
    local total1=$((idle1 + nonidle1))

    sleep 0.2

    read -r cpu user nice system idle iowait irq softirq steal guest guest_nice < /proc/stat

    local idle2=$((idle + iowait))
    local nonidle2=$((user + nice + system + irq + softirq + steal))
    local total2=$((idle2 + nonidle2))

    local totald=$((total2 - total1))
    local idled=$((idle2 - idle1))

    if [ "$totald" -gt 0 ]; then
        awk "BEGIN {printf \"%.1f%%\", (($totald-$idled)/$totald)*100}"
    else
        echo "0.0%"
    fi
}

while true; do

    get_disk

    HOST=$(hostname)
    IP=$(hostname -I | awk '{print $1}')
    UPTIME=$(uptime -p | sed 's/up //')

    RAM=$(free -h | awk '/Mem:/ {print $3 " / " $2}')
    CPU=$(get_cpu_usage)

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

    clear

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
    echo -e " CPU Usage:       $CPU"
    echo -e " Memory:          $RAM"
    echo -e " Storage:         $DISK_CACHE"
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
    echo -n " Select option: "

    read -t 2 -n 1 choice

    if [ $? -ne 0 ]; then
        continue
    fi

    echo
    echo

    case "$choice" in

        1)
            clear
            echo "=== SYSTEM DASHBOARD ==="
            echo
            echo "Hostname: $HOST"
            echo "IP:       $IP"
            echo "Uptime:   $UPTIME"
            echo
            echo "CPU:      $CPU"
            echo "Memory:   $RAM"
            echo "Storage:  $DISK_CACHE"
            echo
            uptime
            echo
            free -h
            pause_menu
            ;;

        2)
            clear
            echo "=== STORAGE ==="
            echo
            lsblk
            echo
            df -h
            pause_menu
            ;;

        3)
            clear
            echo "=== USERS ==="
            echo
            awk -F: '$3 >= 1000 {print $1}' /etc/passwd
            pause_menu
            ;;

        4)
            clear
            echo "=== NETWORK ==="
            echo
            ip -br addr
            echo
            ip route
            pause_menu
            ;;

        5)
            clear
            echo "=== SERVICES ==="
            echo
            systemctl --failed
            pause_menu
            ;;

        6)
            clear
            echo "=== BACKUP ==="
            echo
            echo "Backup system not configured yet."
            pause_menu
            ;;

        7)
            clear
            echo "=== SYSTEM UPDATE ==="
            echo
            apt update
            apt upgrade
            pause_menu
            ;;

        8)
            clear
            echo -e "${YELLOW}=== ADVANCED TERMINAL ===${RESET}"
            echo
            echo "Type 'exit' to return to SLAN."
            echo
            bash
            ;;

        0)
            clear
            echo "=== POWER MENU ==="
            echo
            echo " 1) Restart server"
            echo " 2) Shutdown server"
            echo " 0) Cancel"
            echo
            read -p " Select option: " power

            case "$power" in
                1)
                    echo "Restarting server..."
                    reboot
                    ;;
                2)
                    echo "Shutting down server..."
                    poweroff
                    ;;
                0)
                    ;;
            esac
            ;;

    esac

done
