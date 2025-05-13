#include <iostream>
#include <chrono>
#include <format>
#include <string>
#include <sstream>

bool isFriday13(std::chrono::year_month_day date) {
  if (static_cast<unsigned>(date.day()) != 13)
    return false;

  std::chrono::sys_days sd{date};
  std::chrono::weekday wd{sd};
  return wd == std::chrono::Friday;
}

std::chrono::year_month_day parseDate(const std::string& str) {
  int year, month, day;
  char sep1, sep2;
  std::istringstream ss(str);
  ss >> year >> sep1 >> month >> sep2 >> day;
  
  if (sep1 != '-' || sep2 != '-' || ss.fail()) {
    throw std::runtime_error("Ugyldig datoformat. Bruk YYYY-MM-DD.");
  }

  return std::chrono::year{year} /
         std::chrono::month{static_cast<unsigned>(month)} /
         std::chrono::day{static_cast<unsigned>(day)};
}

int main() {
  std::string input;
  std::cout << "Skriv inn en dato (YYYY-MM-DD): ";
  std::getline(std::cin, input);
  int count = 1;
  try {
    std::chrono::year_month_day start_date = parseDate(input);
    std::chrono::sys_days current{start_date};

    while (true) {
      std::chrono::year_month_day ymd{current};
      if (isFriday13(ymd)) {
        std::cout << "Det er: " << count << " dager til Fredag den 13\n" << std::format("Nærmeste fredag den 13: {}\n", ymd) << "\n";
        break;
      }
      current += std::chrono::days{1};
      count++;
    }

  } catch (const std::exception& e) {
    std::cerr << "Feil: " << e.what() << '\n';
    return 1;
  }
    return 0;
}
