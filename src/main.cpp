#include <iostream>

bool check_symol_point(std::string ip_add) {
    int points = 0;

    for (int i = 0; i < ip_add.length(); ++i) {
        if (ip_add[i] == '.' && ip_add[i + 1] == '.'
            || ip_add[0] == '.' || ip_add[ip_add.length() - 1] == '.') {
            return false;
        }
        else if (ip_add[i] < '0' && ip_add[i] != '.'
            || ip_add[i] > '9') {
            return false;
        }
        else if (ip_add[i] == '.') {
            points++;
        }
    }

    return (points != 3) ? false : true;
}

std::string get_address_part(std::string ip_add, int octet_number) {
    int points = 0;
    std::string str = "";

    for (int i = 0; i < ip_add.length(); ++i) {

        if (points < octet_number) {
            if (points == 3) {
                if (i == ip_add.length() - 1) {
                    return str;
                }
                str += ip_add[i];
            }
            else if (points < 3) {
                if (ip_add[i] == '.')
                    points++;
            }
        }
        else if (points == octet_number) {
            if (ip_add[i] == '.') {
                return str;
            }
            str += ip_add[i];
        }
    }
    return str;
}

bool check_valid_address(std::string ip_address) {
   
    if (!check_symol_point(ip_address)) {
        return false;
    }

    for (int i = 0; i < 4; ++i) {
        std::string str = get_address_part(ip_address, i);

        if (str.length() > 3) {
            return false;
        }

        int octet = 0;
       
        for (int j = 0; j <= str.length() - 1; ++j) {

            if (str.length() == 3) {
                if (str[0] == '0' && str[1] == '0' && str[2] == '0'
                    || str[0] == '0' && str[1] == '0' && str[2] > '0'
                    || str[0] == '0' && str[1] > '0') {
                    return false;
                }

                octet += int(str[j] - '0');

                if (j < 2) {
                    octet *= 10;
                }
            }
            else if (str.length() == 2) {
                if (str[0] == '0' && str[1] == '0' || str[0] == '0' && str[1] > '0') {
                    return false;
                }

                octet += int(str[j] - '0');

                if (j == 0) {
                    octet *= 10;
                }
            }
            else if (str.length() == 1) {
                octet += int(str[j] - '0');
            }
        }

        if (octet > 255) {
            return false;
        }
    }
    return true;
}

int main() {
    std::string ip_address;
    std::cout << "Input IP Address: ";
    std::getline(std::cin, ip_address);

    check_valid_address(ip_address) ? (std::cout << "Valid" << std::endl) :
        (std::cout << "Invalid" << std::endl);
}