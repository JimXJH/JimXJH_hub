#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<random>
#include<chrono>
#include<algorithm>
#include<functional>
#include<tuple>
#include <unordered_set>
#include<set>
#include<map>
#include <cstdlib>
#include <future>
#include <atomic>
#include <memory>
using namespace std;
extern mt19937_64 gen;



class Polyomino_5
{
	template<typename T>
	friend bool build_area(vector<vector<short>>& f_plate, const int n_fill, vector<T> p_plate);
	template<typename T, typename T_new>
	friend void build_Polyomino_plate(const vector<T> plate, vector<T_new>& new_plate_return);
	friend vector<pair<short, short>> normalize_polyomino(const vector<pair<short, short>>& coords);
	friend ostream& operator<<(ostream& cout, Polyomino_5 p);
private:
	vector<pair<short, short>> polyomino;
public:
	Polyomino_5();
	Polyomino_5(short x2, short y2, short x3, short y3, short x4, short y4, short x5, short y5);
	Polyomino_5(pair<short, short> p2);
	~Polyomino_5();
};

class Polyomino_6
{
	template<typename T>
	friend bool build_area(vector<vector<short>>& f_plate, const int n_fill, vector<T> p_plate);
	template<typename T, typename T_new>
	friend void build_Polyomino_plate(const vector<T> plate, vector<T_new>& new_plate_return);
	friend vector<pair<short, short>> normalize_polyomino(const vector<pair<short, short>>& coords);
	friend ostream& operator<<(ostream& cout, Polyomino_6);
	
private:
	vector<pair<short, short>> polyomino;
public:
	Polyomino_6();
	Polyomino_6(pair<short,short> p2);
	~Polyomino_6();
};

class Polyomino_7
{
	template<typename T>
	friend bool build_area(vector<vector<short>>& f_plate, const int n_fill, vector<T> p_plate);
	template<typename T, typename T_new>
	friend void build_Polyomino_plate(const vector<T> plate, vector<T_new>& new_plate_return);
	friend vector<pair<short, short>> normalize_polyomino(const vector<pair<short, short>>& coords);
	friend ostream& operator<<(ostream& cout, Polyomino_7);

private:
	vector<pair<short, short>> polyomino;
public:
	Polyomino_7();
	Polyomino_7(pair<short, short> p2);
	~Polyomino_7();
};

class Polyomino_8
{
	template<typename T>
	friend bool build_area(vector<vector<short>>& f_plate, const int n_fill, vector<T> p_plate);
	template<typename T, typename T_new>
	friend void build_Polyomino_plate(const vector<T> plate, vector<T_new>& new_plate_return);
	friend vector<pair<short, short>> normalize_polyomino(const vector<pair<short, short>>& coords);
	friend ostream& operator<<(ostream& cout, Polyomino_8);

private:
	vector<pair<short, short>> polyomino;
public:
	Polyomino_8();
	Polyomino_8(pair<short, short> p2);
	~Polyomino_8();
};

class Polyomino_9
{
	template<typename T>
	friend bool build_area(vector<vector<short>>& f_plate, const int n_fill, vector<T> p_plate);
	template<typename T, typename T_new>
	friend void build_Polyomino_plate(const vector<T> plate, vector<T_new>& new_plate_return);
    friend vector<pair<short, short>> normalize_polyomino(const vector<pair<short, short>>& coords);
	friend ostream& operator<<(ostream& cout, Polyomino_9);

private:
	vector<pair<short, short>> polyomino;
public:
	Polyomino_9();
	Polyomino_9(pair<short, short> p2);
	~Polyomino_9();
};

ostream& operator<<(ostream& cout, Polyomino_5 p);
ostream& operator<<(ostream& cout, Polyomino_6 p);
ostream& operator<<(ostream& cout, Polyomino_7 p);
ostream& operator<<(ostream& cout, Polyomino_8 p);
ostream& operator<<(ostream& cout, Polyomino_9 p);

extern Polyomino_5 area_plate[63];
extern vector<Polyomino_5> P5_plate;


vector<pair<short, short>> normalize_polyomino(const vector<pair<short, short>>& coords);

// 函数模板：生成n联骨牌
template<typename T, typename T_new>
void build_Polyomino_plate(const vector<T> plate, vector<T_new>& new_plate_return) {
    // 方向：右(0,1), 左(0,-1), 上(-1,0), 下(1,0)
    vector<pair<short, short>> directions = { {0,1}, {0,-1}, {1,0}, {-1,0} };
    // 存储已见过的标准骨牌表示
    set<vector<pair<short, short>>> seen;

    for (const T& piece : plate) {
        // 收集原骨牌的所有坐标（包括基准点(0,0)）
        vector<pair<short, short>> allCoords = { {0,0} }; // 基准点
        for (const auto& p : piece.polyomino) {
            allCoords.push_back(p);
        }

        // 尝试在现有骨牌的每个格子的每个方向添加新格子
        for (const auto& cell : allCoords) {
            for (const auto& dir : directions) {
                pair<short, short> newCell = { cell.first + dir.first, cell.second + dir.second };

                // 检查新格子是否已存在
                if (find(allCoords.begin(), allCoords.end(), newCell) != allCoords.end()) {
                    continue;
                }

                // 检查新格子是否满足条件：i>=0，且当i=0时j>0
                if (newCell.first < 0) continue;
                if (newCell.first == 0 && newCell.second <= 0) continue;

                // 创建包含新格子的坐标集合
                vector<pair<short, short>> newAllCoords = allCoords;
                newAllCoords.push_back(newCell);

                // 标准化新骨牌（只平移和排序）
                vector<pair<short, short>> standard = normalize_polyomino(newAllCoords);

                // 检查是否已存在（只比较平移后的坐标集合）
                if (seen.find(standard) == seen.end()) {
                    seen.insert(standard);

                    // 构建新骨牌对象
                    T_new new_piece;
                    // 添加偏移点（跳过基准点(0,0)）
                    for (const auto& p : newAllCoords) {
                        if (p.first == 0 && p.second == 0) continue;
                        new_piece.polyomino.push_back(p);
                    }
                    // 添加到结果集
                    new_plate_return.push_back(new_piece);
                }
            }
        }
    }
}

// 舞蹈链节点结构
struct DLXNode {
    DLXNode* left, * right, * up, * down;
    DLXNode* colRoot;
    int rowID;
    int colID;
    int nodeCount; // 列头节点专用：该列节点数
};

// 舞蹈链求解器类
class DLXSolver {
private:
    int numCols;
    DLXNode* header;
    vector<DLXNode*> colHeaders;
    vector<vector<int>> solutions;
    // 将元组修改为四个元素：(行ID, 方块索引, 基准点x, 基准点y)
    vector<tuple<int, int, int, int>> rowInfo; // 修正为四元素元组
    mt19937_64& gen;

    // 创建舞蹈链节点
    DLXNode* createNode(int row = -1, int col = -1) {
        DLXNode* node = new DLXNode();
        node->left = node->right = node->up = node->down = node;
        node->colRoot = nullptr;
        node->rowID = row;
        node->colID = col;
        node->nodeCount = 0;
        return node;
    }

    // 初始化舞蹈链结构
    void init(int cols) {
        numCols = cols;
        header = createNode(-1, -1);
        colHeaders.resize(cols);

        // 创建列头节点并形成环形链表
        DLXNode* prev = header;
        for (int i = 0; i < cols; ++i) {
            DLXNode* colNode = createNode(-1, i);
            colHeaders[i] = colNode;

            colNode->right = header;
            colNode->left = prev;
            prev->right = colNode;
            header->left = colNode;
            prev = colNode;
        }
    }

    // 添加节点到列中
    void addNodeToColumn(int col, DLXNode* node) {
        DLXNode* colHeader = colHeaders[col];
        colHeader->nodeCount++;

        node->down = colHeader;
        node->up = colHeader->up;
        colHeader->up->down = node;
        colHeader->up = node;
        node->colRoot = colHeader;
    }

    // 覆盖列操作
    void coverColumn(DLXNode* colNode) {
        colNode->right->left = colNode->left;
        colNode->left->right = colNode->right;

        for (DLXNode* rowNode = colNode->down; rowNode != colNode; rowNode = rowNode->down) {
            for (DLXNode* cellNode = rowNode->right; cellNode != rowNode; cellNode = cellNode->right) {
                cellNode->up->down = cellNode->down;
                cellNode->down->up = cellNode->up;
                cellNode->colRoot->nodeCount--;
            }
        }
    }

    // 取消覆盖列操作
    void uncoverColumn(DLXNode* colNode) {
        for (DLXNode* rowNode = colNode->up; rowNode != colNode; rowNode = rowNode->up) {
            for (DLXNode* cellNode = rowNode->left; cellNode != rowNode; cellNode = cellNode->left) {
                cellNode->up->down = cellNode;
                cellNode->down->up = cellNode;
                cellNode->colRoot->nodeCount++;
            }
        }

        colNode->right->left = colNode;
        colNode->left->right = colNode;
    }

    // 选择列启发式策略
    DLXNode* selectColumn() {
        DLXNode* bestCol = header->right;
        for (DLXNode* colNode = header->right; colNode != header; colNode = colNode->right) {
            if (colNode->nodeCount < bestCol->nodeCount) {
                bestCol = colNode;
            }
        }
        return bestCol;
    }

    // 递归求解函数
    bool solveRecursive(vector<int>& solution) {
        if (header->right == header) {
            solutions.push_back(solution);
            return true;
        }

        DLXNode* colNode = selectColumn();
        if (colNode->nodeCount == 0) return false;

        coverColumn(colNode);

        // 收集当前列的所有行
        vector<DLXNode*> rowNodes;
        for (DLXNode* rowNode = colNode->down; rowNode != colNode; rowNode = rowNode->down) {
            rowNodes.push_back(rowNode);
        }

        // 随机打乱行顺序以实现随机解
        shuffle(rowNodes.begin(), rowNodes.end(), gen);

        for (DLXNode* rowNode : rowNodes) {
            solution.push_back(rowNode->rowID);

            // 覆盖当前行中所有节点所在的列
            for (DLXNode* cellNode = rowNode->right; cellNode != rowNode; cellNode = cellNode->right) {
                coverColumn(cellNode->colRoot);
            }

            if (solveRecursive(solution)) {
                return true;
            }

            // 回溯
            solution.pop_back();
            for (DLXNode* cellNode = rowNode->left; cellNode != rowNode; cellNode = cellNode->left) {
                uncoverColumn(cellNode->colRoot);
            }
        }

        uncoverColumn(colNode);
        return false;
    }

public:
    DLXSolver(int cols, mt19937_64& rng) : numCols(cols), gen(rng) {
        init(cols);
    }

    ~DLXSolver() {
        // 清理内存
        for (auto col : colHeaders) {
            DLXNode* node = col->down;
            while (node != col) {
                DLXNode* temp = node;
                node = node->down;
                delete temp;
            }
            delete col;
        }
        delete header;
    }

    // 添加行到舞蹈链
    void addRow(int rowID, const vector<int>& columns) {
        if (columns.empty()) return;

        DLXNode* firstNode = nullptr;
        DLXNode* prevNode = nullptr;

        for (int col : columns) {
            DLXNode* node = createNode(rowID, col);
            if (!firstNode) firstNode = node;

            addNodeToColumn(col, node);

            // 水平链接
            if (prevNode) {
                node->left = prevNode;
                node->right = prevNode->right;
                prevNode->right->left = node;
                prevNode->right = node;
            }
            prevNode = node;
        }

        // 完成水平环形链接
        if (firstNode && prevNode) {
            firstNode->left = prevNode;
            prevNode->right = firstNode;
        }
    }

    // 添加行信息时使用四元素元组
    void addRowInfo(int rowID, int pieceIndex, int x, int y) {
        rowInfo.push_back(make_tuple(rowID, pieceIndex, x, y)); // 存储四个值
    }

    // 求解入口
    bool solve(vector<int>& solution) {
        return solveRecursive(solution);
    }

    // 返回四元素元组的引用
    const vector<tuple<int, int, int, int>>& getRowInfo() const {
        return rowInfo;
    }
};

// 主函数模板实现
template<typename T>
bool build_area(vector<vector<short>>& f_plate, const int n_fill, vector<T> p_plate) {
    int n = f_plate.size();
    if (n == 0) return true;

    int totalCells = n * n;
    DLXSolver solver(totalCells, gen);
    int rowCounter = 0;

    // 遍历所有方块
    for (int p_idx = 0; p_idx < p_plate.size(); ++p_idx) {
        const T& piece = p_plate[p_idx];

        // 遍历所有可能的基准点位置
        for (int x = 0; x < n; ++x) {
            for (int y = 0; y < n; ++y) {
                vector<pair<int, int>> coveredCells;
                coveredCells.push_back({ x, y }); // 基准点

                bool validPlacement = true;

                // 检查所有偏移位置
                for (const auto& offset : piece.polyomino) {
                    int nx = x + offset.first;
                    int ny = y + offset.second;

                    // 检查边界
                    if (nx < 0 || nx >= n || ny < 0 || ny >= n) {
                        validPlacement = false;
                        break;
                    }

                    coveredCells.push_back({ nx, ny });
                }

                if (!validPlacement) continue;

                // 检查是否有重复单元格
                unordered_set<int> cellSet;
                for (const auto& cell : coveredCells) {
                    int cellIdx = cell.first * n + cell.second;
                    if (cellSet.find(cellIdx) != cellSet.end()) {
                        validPlacement = false;
                        break;
                    }
                    cellSet.insert(cellIdx);
                }

                if (!validPlacement) continue;

                // 收集覆盖的列索引
                vector<int> columns;
                for (const auto& cell : coveredCells) {
                    columns.push_back(cell.first * n + cell.second);
                }

                // 添加到舞蹈链
                solver.addRow(rowCounter, columns);
                solver.addRowInfo(rowCounter, p_idx, x, y);
                rowCounter++;
            }
        }
    }

    // 尝试求解
    vector<int> solution;
    bool found = solver.solve(solution);

    if (found) {
        short mark = 1;
        const auto& rowInfo = solver.getRowInfo();

        for (int rowID : solution) {
            for (const auto& info : rowInfo) {
                if (get<0>(info) == rowID) { // 行ID
                    int p_idx = get<1>(info); // 方块索引
                    int baseX = get<2>(info); // 基准点x
                    int baseY = get<3>(info); // 基准点y (索引改为3)

                    // 标记基准点
                    f_plate[baseX][baseY] = mark;

                    // 标记偏移点
                    for (const auto& offset : p_plate[p_idx].polyomino) {
                        int x = baseX + offset.first;
                        int y = baseY + offset.second;
                        f_plate[x][y] = mark;
                    }
                    mark++;
                    break;
                }
            }
        }
        return true;
    }

    return false;
}