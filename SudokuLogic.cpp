#include <iostream>
#include <fstream>
#include <vector>
#include<map>
#include <tuple>
#include <algorithm>
#include <cstdlib>
#include<chrono>
#include<random>
using namespace std;

mt19937_64 gen(chrono::system_clock::now().time_since_epoch().count());//全局随机数引擎

// 舞蹈链节点结构
struct Node {
    Node* U, * D, * L, * R;
    int row, col;
    int size; // 列头节点使用：该列节点数
    Node(int r, int c) : row(r), col(c), U(this), D(this), L(this), R(this), size(0) {}
};

// 舞蹈链类
class DLX {
public:
    vector<Node*> col_headers;
    Node* head;
    vector<int> solution;
    int ncol;
    int row_count;

    DLX(int num_cols) : ncol(num_cols), row_count(0) {
        head = new Node(-1, -1);
        col_headers.resize(num_cols, nullptr);
        for (int i = 0; i < num_cols; i++) {
            col_headers[i] = new Node(-1, i);
            col_headers[i]->L = head->L;
            col_headers[i]->R = head;
            head->L->R = col_headers[i];
            head->L = col_headers[i];
        }
    }

    ~DLX() {
        // 简化：实际应用中需释放内存
    }

    void add_row(vector<int> const& cols) {
        if (cols.empty()) return;
        Node* row_header = nullptr;
        Node* prev = nullptr;
        for (int c : cols) {
            Node* p = new Node(row_count, c);
            Node* col_header = col_headers[c];
            // 插入列链表
            p->U = col_header->U;
            p->D = col_header;
            col_header->U->D = p;
            col_header->U = p;
            col_header->size++;
            // 插入行链表
            if (row_header == nullptr) {
                row_header = p;
                prev = p;
            }
            else {
                p->L = prev;
                p->R = row_header;
                prev->R = p;
                row_header->L = p;
                prev = p;
            }
        }
        row_count++;
    }

    void cover(Node* col) {
        col->L->R = col->R;
        col->R->L = col->L;
        for (Node* i = col->D; i != col; i = i->D) {
            for (Node* j = i->R; j != i; j = j->R) {
                j->U->D = j->D;
                j->D->U = j->U;
                col_headers[j->col]->size--;
            }
        }
    }

    void uncover(Node* col) {
        for (Node* i = col->U; i != col; i = i->U) {
            for (Node* j = i->L; j != i; j = j->L) {
                col_headers[j->col]->size++;
                j->U->D = j;
                j->D->U = j;
            }
        }
        col->L->R = col;
        col->R->L = col;
    }

    bool solve() {
        if (head->R == head) return true;
        Node* col = head->R;
        int min_size = col->size;
        // 选择节点数最少的列
        for (Node* c = col->R; c != head; c = c->R) {
            if (c->size < min_size) {
                col = c;
                min_size = c->size;
                if (min_size == 0) break;
            }
        }
        if (min_size == 0) return false;
        cover(col);
        for (Node* i = col->D; i != col; i = i->D) {
            solution.push_back(i->row);
            for (Node* j = i->R; j != i; j = j->R) {
                cover(col_headers[j->col]);
            }
            if (solve()) return true;
            solution.pop_back();
            for (Node* j = i->L; j != i; j = j->L) {
                uncover(col_headers[j->col]);
            }
        }
        uncover(col);
        return false;
    }
};

// 构建答案盘面函数
bool build_ans_plate(const vector<vector<int>>& v_area_plate, const int line, vector<vector<int>>& v_ans_plate) {
    int ncol = 4 * line * line;
    DLX dlx(ncol);
    vector<tuple<int, int, int>> row_map; // 行号 -> (row, col, k)

    for (int row = 0; row < line; row++) {
        for (int col = 0; col < line; col++) {
            for (int k = 0; k < line; k++) {
                vector<int> cols;
                cols.push_back(row * line + col); // 格子约束
                cols.push_back(line * line + row * line + k); // 行约束
                cols.push_back(2 * line * line + col * line + k); // 列约束
                int area_id = v_area_plate[row][col];
                cols.push_back(3 * line * line + (area_id - 1) * line + k); // 区域约束
                dlx.add_row(cols);
                row_map.push_back(make_tuple(row, col, k));
            }
        }
    }

    if (dlx.solve()) {
        for (int row_index : dlx.solution) {
            auto t = row_map[row_index];
            int r = get<0>(t);
            int c = get<1>(t);
            int k = get<2>(t);
            v_ans_plate[r][c] = k + 1; // 转换为1~N
        }
        return true;
    }
    return false;
}

class DLXCounter {
public:
    vector<Node*> col_headers;
    Node* head;
    int ncol;
    int row_count;
    int _count;
    int _max_count;

    DLXCounter(int num_cols) : ncol(num_cols), row_count(0), _count(0), _max_count(0) {
        head = new Node(-1, -1);
        col_headers.resize(num_cols, nullptr);
        for (int i = 0; i < num_cols; i++) {
            col_headers[i] = new Node(-1, i);
            col_headers[i]->L = head->L;
            col_headers[i]->R = head;
            head->L->R = col_headers[i];
            head->L = col_headers[i];
        }
    }

    ~DLXCounter() {
        // 简化：实际应用中需释放内存
    }

    void add_row(vector<int> const& cols) {
        if (cols.empty()) return;
        Node* row_header = nullptr;
        Node* prev = nullptr;
        for (int c : cols) {
            Node* p = new Node(row_count, c);
            Node* col_header = col_headers[c];
            p->U = col_header->U;
            p->D = col_header;
            col_header->U->D = p;
            col_header->U = p;
            col_header->size++;
            if (row_header == nullptr) {
                row_header = p;
                prev = p;
            }
            else {
                p->L = prev;
                p->R = row_header;
                prev->R = p;
                row_header->L = p;
                prev = p;
            }
        }
        row_count++;
    }

    void cover(Node* col) {
        col->L->R = col->R;
        col->R->L = col->L;
        for (Node* i = col->D; i != col; i = i->D) {
            for (Node* j = i->R; j != i; j = j->R) {
                j->U->D = j->D;
                j->D->U = j->U;
                col_headers[j->col]->size--;
            }
        }
    }

    void uncover(Node* col) {
        for (Node* i = col->U; i != col; i = i->U) {
            for (Node* j = i->L; j != i; j = j->L) {
                col_headers[j->col]->size++;
                j->U->D = j;
                j->D->U = j;
            }
        }
        col->L->R = col;
        col->R->L = col;
    }

    int count_solutions(int max_count) {
        _count = 0;
        _max_count = max_count;
        _solve_count();
        return _count;
    }

    void _solve_count() {
        if (_count >= _max_count) return;
        if (head->R == head) {
            _count++;
            return;
        }
        Node* col = head->R;
        int min_size = col->size;
        for (Node* c = col->R; c != head; c = c->R) {
            if (c->size < min_size) {
                col = c;
                min_size = c->size;
                if (min_size == 0) break;
            }
        }
        if (min_size == 0) return;
        cover(col);
        for (Node* i = col->D; i != col; i = i->D) {
            for (Node* j = i->R; j != i; j = j->R) {
                cover(col_headers[j->col]);
            }
            _solve_count();
            for (Node* j = i->L; j != i; j = j->L) {
                uncover(col_headers[j->col]);
            }
            if (_count >= _max_count) break;
        }
        uncover(col);
    }
};

static bool check_unique(const vector<vector<int>>& board, const vector<vector<int>>& areas, int line) {
    DLXCounter dlx(4 * line * line);
    for (int r = 0; r < line; r++) {
        for (int c = 0; c < line; c++) {
            int area_id = areas[r][c];
            if (board[r][c] != 0) {
                int k = board[r][c] - 1;
                vector<int> cols;
                cols.push_back(r * line + c);
                cols.push_back(line * line + r * line + k);
                cols.push_back(2 * line * line + c * line + k);
                cols.push_back(3 * line * line + (area_id - 1) * line + k);
                dlx.add_row(cols);
            }
            else {
                for (int k = 0; k < line; k++) {
                    vector<int> cols;
                    cols.push_back(r * line + c);
                    cols.push_back(line * line + r * line + k);
                    cols.push_back(2 * line * line + c * line + k);
                    cols.push_back(3 * line * line + (area_id - 1) * line + k);
                    dlx.add_row(cols);
                }
            }
        }
    }
    int count = dlx.count_solutions(2);
    return count == 1;
}

void build_ori_plate(const vector<vector<int>>& v_area_plate, const int line, const vector<vector<int>>& v_ans_plate, vector<vector<int>>& v_ori_plate) {
    v_ori_plate = v_ans_plate;
    vector<pair<int, int>> indices;
    for (int i = 0; i < line; i++) {
        for (int j = 0; j < line; j++) {
            indices.push_back({ i, j });
        }
    }
    shuffle(indices.begin(), indices.end(), gen);
    for (auto& idx : indices) {
        int r = idx.first, c = idx.second;
        int temp = v_ori_plate[r][c];
        v_ori_plate[r][c] = 0;
        if (!check_unique(v_ori_plate, v_area_plate, line)) {
            v_ori_plate[r][c] = temp;
        }
    }
}

void build_fill_plate(const int line, const vector<vector<int>>& v_ans_plate, vector<vector<int>>& v_ori_plate)
{
    int numbers = 0;
    for (int i = 0;i < line;i++)
    {
        for (int j = 0;j < line;j++)
        {
            if (v_ori_plate[i][j])
            {
                numbers++;
            }
        }
    }

    int min_n = line * line * 10 / 23  + 1;
    while (numbers < min_n)
    {
        int x = uniform_int_distribution<int>(0, line - 1)(gen);
        int y = uniform_int_distribution<int>(0, line - 1)(gen);
        if (v_ori_plate[x][y] == 0)
        {
            v_ori_plate[x][y] = v_ans_plate[x][y];
            numbers++;
        }
    }
    return;
}

void final_func(const int line, vector<vector<int>>& v_area_plate, vector<vector<int>>& v_ori_plate, vector<vector<int>>& v_ans_plate, map<pair<int,int>,int>& map_area_plate)
{
    v_area_plate = vector<vector<int>>(line, vector<int>(line, 0));
    v_ori_plate = vector<vector<int>>(line, vector<int>(line, 0));
    v_ans_plate = vector<vector<int>>(line, vector<int>(line, 0));
    map_area_plate = map<pair<int, int>, int>();
    int length = 0;
    int target = 0;
    ifstream ifs;
    switch (line) {
    case 5: ifs.open("5联骨牌盘面.txt", ios::in | ios::binary); length = 62; target = uniform_int_distribution<int>(0, 487)(gen); break;
    case 6: ifs.open("6联骨牌盘面.txt", ios::in | ios::binary); length = 86; target = uniform_int_distribution<int>(0, 485)(gen); break;
    case 7: ifs.open("7联骨牌盘面.txt", ios::in | ios::binary); length = 114; target = uniform_int_distribution<int>(0, 92)(gen); break;
    case 8: ifs.open("8联骨牌盘面（最终版50个）.txt", ios::in | ios::binary); length = 146; target = uniform_int_distribution<int>(0, 49)(gen); break;
    case 9: ifs.open("9联骨牌盘面（最终版50个）.txt", ios::in | ios::binary); length = 182; target = uniform_int_distribution<int>(0, 49)(gen); break;
    }

    if (ifs.is_open()) {
        ifs.seekg(target * length, ios::beg);
        int c = 0;
        for (int i = 0; i < line; i++) {
            for (int j = 0; j < line; j++) {
                ifs >> c;
                v_area_plate[i][j] = c;
                map_area_plate[pair<int, int>(i, j)] = c;
            }
        }
        ifs.close();
    }
    else
    {
        cout << "文件打开失败，line = " << line << endl;
    }

    /*
    for (int i = 0;i < line;i++)
    {
        for (int j = 0;j < line;j++)
        {
            cout << v_area_plate[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/


    build_ans_plate(v_area_plate, line, v_ans_plate);

    build_ori_plate(v_area_plate,line,v_ans_plate,v_ori_plate);

    build_fill_plate(line,v_ans_plate,v_ori_plate);

    /*
    for (int i = 0;i < line;i++)
    {
        for (int j = 0;j < line;j++)
        {
            cout << v_ori_plate[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/

    return;
}