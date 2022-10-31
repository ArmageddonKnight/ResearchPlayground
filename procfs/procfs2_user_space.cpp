#include <fstream>

#define C_PROC_FILENAME "buffer1k"

int main() {
  std::ofstream fout("/proc/" C_PROC_FILENAME);

  fout << "Hi Bojian";
  fout << "Hi Linux. How are u doing?";

  fout.close();

  return 0;
}
