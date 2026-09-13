#!/bin/bash

while true; do
    clear

    echo "=========================================="
    echo "         SLAN COMPANY SERVER"
    echo "=========================================="
    echo ""
    echo " Hostname: $(hostname)"
    echo " IP:       $(hostname -I | awk '{print $1}')"
    echo " Uptime:   $(uptime -p)"
    echo ""
    echo "------------------------------------------"
    echo " 1) Server status"
    echo " 2) Disk usage"
    echo " 3) Network information"
    echo " 4) Check services"
    echo " 5) Update server"
    echo " 6) Advanced terminal"
    echo " 0) Shutdown / Restart"
    echo "------------------------------------------"
    echo ""

    read -p "Select option: " choice

    case "$choice" in

        1)
            clear
            echo "SERVER STATUS"
            echo
            uptime
            echo
            free -h
            echo
            df -h
            read -p "Press ENTER..."
            ;;

        2)
            clear
            df -h
            read -p "Press ENTER..."
            ;;

        3)
            clear
            ip addr
            read -p "Press ENTER..."
            ;;

        4)
            clear
            systemctl --failed
            read -p "Press ENTER..."
            ;;

        5)
            sudo apt update
            sudo apt upgrade
            read -p "Press ENTER..."
            ;;

        6)
            clear
            echo "Type 'exit' to return to the server menu."
            bash
            ;;

        0)
            clear
            echo "1) Restart"
            echo "2) Shutdown"
            echo "3) Cancel"
            read -p "> " power

            case "$power" in
                1) sudo reboot ;;
                2) sudo poweroff ;;
            esac
            ;;

    esac
done
