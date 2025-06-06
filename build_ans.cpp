#include"Head.h"

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
    atomic<bool>* p_timeout_flag = nullptr; // 超时标志指针

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
        // 检查超时标志
        if (p_timeout_flag && *p_timeout_flag) {
            return false;
        }
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

// 构建答案盘面函数（增加超时标志参数）
bool build_ans_plate(const vector<vector<short>>& v_area_plate, short n, vector<vector<short>>& v_ans_plate, atomic<bool>* timeout_flag) {
    int ncol = 4 * n * n;
    DLX dlx(ncol);
    dlx.p_timeout_flag = timeout_flag; // 设置超时标志
    vector<tuple<int, int, int>> row_map; // 行号 -> (row, col, k)

    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            for (int k = 0; k < n; k++) {
                vector<int> cols;
                cols.push_back(row * n + col); // 格子约束
                cols.push_back(n * n + row * n + k); // 行约束
                cols.push_back(2 * n * n + col * n + k); // 列约束
                int area_id = v_area_plate[row][col];
                cols.push_back(3 * n * n + (area_id - 1) * n + k); // 区域约束
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

bool test_ans(const int line, const vector<vector<short>>& v_area_plate) 
{
    map<short, vector<pair<short, short>>> map_area_plate;
    for (short i = 0; i < line; i++) {
        map_area_plate[i + 1] = vector<pair<short, short>>();
    }

    // 使用智能指针管理共享数据
    auto area_plate_ptr = make_shared<vector<vector<short>>>(v_area_plate);
    auto ans_plate_ptr = make_shared<vector<vector<short>>>(line, vector<short>(line, 0));
    auto timeout_flag_ptr = make_shared<atomic<bool>>(false);
    bool solved = false;

    // 使用异步任务
    future<bool> fut = async(launch::async, [area_plate_ptr, line, ans_plate_ptr, timeout_flag_ptr]() {
        return build_ans_plate(*area_plate_ptr, line, *ans_plate_ptr, timeout_flag_ptr.get());
        });

    // 设置10秒超时
    future_status status = fut.wait_for(chrono::seconds(10));
    if (status == future_status::ready) {
        solved = fut.get();
    }
    else {
        // 超时处理
        *timeout_flag_ptr = true; // 设置超时标志
        shared_future<bool> shfut = fut.share(); // 转为shared_future
        status = shfut.wait_for(chrono::seconds(1)); // 再等待1秒
        if (status == future_status::ready) {
            solved = shfut.get();
        }
        else {
            solved = false;
            // 后台线程处理剩余任务
            thread([shfut]() {
                try {
                    shfut.get();
                }
                catch (...) {}
                }).detach();
        }
    }

    if (solved)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}