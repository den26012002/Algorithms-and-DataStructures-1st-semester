#include<fstream>
#include<map>
#include<queue>
#include<vector>
#include<string>

std::ifstream fin("quack.in");
std::ofstream fout("quack.out");

const int MAX_N = 1e5 + 5;

/*struct Queue {
public:
    void push(uint16_t x) {
        inc(top);
        cntElems++;
        arr[top] = x;
    }

    void pop() {
        bottom++;
        cntElems--;
    }

    int front() {
        return arr[bottom];
    }

    bool empty() {
        return !cntElems;
    }

    Queue() {
        top = -1;
        bottom = 0;
        cntElems = 0;
        arr.resize(MAX_N * 10);
    }

    Queue(int maxSize) {
        top = -1;
        bottom = 0;
        cntElems = 0;
        arr.resize(maxSize * 10);
    }
private:
    int top;
    int bottom;
    int cntElems;
    std::vector<uint16_t> arr;

    void inc(int& param) {
        param = (param + 1) % arr.size();
    }
};*/

uint16_t toInt(std::string& str) {
    uint16_t ans = 0;
    for (int i(0); i < str.size(); i++) {
        ans *= 10;
        ans += (str[i] - '0');
    }
    return ans;
}

class QuackInterpreter {
public:
    void enterProgram() {
        std::string str;
        int cnt = 0;
        program.resize(MAX_N);
        subprogram.resize(MAX_N);
        while (std::getline(fin, str)) {
            program[cnt] = str;
            subprogram[cnt] = -1;
            if (str[0] == ':') {
                std::string label = str.substr(1);
                labels[label] = cnt;
            }
            ++cnt;
        }
        program.resize(cnt);
        subprogram.resize(cnt);
        for (int i(0); i < program.size(); ++i) {
            std::string label;
            switch (program[i][0])
            {
            case 'J':
                label = program[i].substr(1);
                subprogram[i] = goTo(label);
                break;
            case 'Z':
                label = program[i].substr(2);
                subprogram[i] = goTo(label);
                break;
            case 'E':
                label = program[i].substr(3);
                subprogram[i] = goTo(label);
                break;
            case 'G':
                label = program[i].substr(3);
                subprogram[i] = goTo(label);
                break;
            default:
                break;

            }
        }
        registers.resize(26);
        for (int i(0); i < 26; ++i) {
            registers[i] = 0;
        }
    }

    void runProgram() {
        int i = 0;
        while (i < program.size()) {
            uint16_t x, y;
            std::string label;
            switch (program[i][0]) {
            case '+':
                x = get();
                y = get();
                put((x + y) % 65536);
                i++;
                break;
            case '-':
                x = get();
                y = get();
                put((x - y) % 65536);
                i++;
                break;
            case '*':
                x = get();
                y = get();
                put((x * y) % 65536);
                i++;
                break;
            case '/':
                x = get();
                y = get();
                if (y == 0) {
                    put(0);
                }
                else {
                    put(x / y);
                }
                i++;
                break;
            case '%':
                x = get();
                y = get();
                if (y == 0) {
                    put(0);
                }
                else {
                    put(x % y);
                }
                i++;
                break;
            case '>':
                x = get();
                registers[program[i][1] - 'a'] = x;
                i++;
                break;
            case '<':
                put(registers[program[i][1] - 'a']);
                i++;
                break;
            case 'P':
                if (program[i] == "P" || program[i] == "P\r") {
                    fout << get() << '\n';
                }
                else {
                    fout << registers[program[i][1] - 'a'] << '\n';
                }
                i++;
                break;
            case 'C':
                if (program[i] == "C" || program[i] == "C\r") {
                    fout << (char)(get() % 256);
                }
                else {
                    fout << (char)(registers[program[i][1] - 'a'] % 256);
                }
                i++;
                break;
            case ':':
                i++;
                break;
            case 'J':
                i = subprogram[i];
                break;
            case 'Z':
                if (registers[program[i][1] - 'a'] == 0) {
                    i = subprogram[i];
                }
                else {
                    i++;
                }
                break;
            case 'E':
                if (registers[program[i][1] - 'a'] == registers[program[i][2] - 'a']) {
                    i = subprogram[i];
                }
                else {
                    i++;
                }
                break;
            case 'G':
                if (registers[program[i][1] - 'a'] > registers[program[i][2] - 'a']) {
                    i = subprogram[i];
                }
                else {
                    i++;
                }
                break;
            case 'Q':
                return;
            default:
                put(toInt(program[i]));
                i++;
            }
        }
    }

private:
    std::queue<uint16_t> q;
    std::vector<uint16_t> registers;
    std::map<std::string, uint16_t> labels;
    std::vector<std::string> program;
    std::vector<int> subprogram;

    int get() {
        uint16_t ans = q.front();
        q.pop();
        return ans;
    }

    void put(uint16_t x) {
        q.push(x);
    }

    int goTo(std::string& label) {
        return labels[label];
    }
};

signed main() {
    fin.sync_with_stdio(false);
    fout.tie(0);
    QuackInterpreter qi;
    qi.enterProgram();
    qi.runProgram();


    return 0;
}