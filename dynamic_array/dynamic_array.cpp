#include <iostream>
#include <string>
#include <sstream>      // std::ostringstream
using namespace std;

int main(void){

    // 3次元配列
	//     Z
	//     |
	//     |
	//     |___________Y
	//    /
	//   /
	//  X

    //
    // 3次元配列のサイズを入力
    //
    string str;

    cout << "?Y >";
    getline(cin, str);
    int Y = stoi(str);

    cout << "?X >";
    getline(cin, str);
    int X = stoi(str);

    cout << "?Z >";
    getline(cin, str);
    int Z = stoi(str);
    
    //
    // 3次元配列の動的確保
    // string型の３次元配列
    //
    string ***cube = new string**[Z];
    for (int z = 0; z < Z; z++) {
        cube[z] = new string*[X];
        for (int x = 0; x < X; x++) {
            cube[z][x] = new string[Y];
        }
    }
    
    //
    // 配列へのアクセス
    //

    // テスト用に適当なデータを設定する
    // (Z,X,Y) の形式で文字列データを設定
    for( int z = 0; z < Z; z++ ){
        for( int x = 0; x < X; x++ ){
            for( int y = 0; y < Y; y++ ){
                cube[z][x][y] = "(" + to_string(z) + "," + to_string(x) + "," + to_string(y) + ")";
            }
        }
    }
    
    // テスト用データの出力
    for( int z = 0; z < Z; z++ ){
        cout << "--- z(" << to_string(z) << ") ---" << endl;
        for( int x = 0; x < X; x++ ){
            for( int y = 0; y < Y; y++ ){
                cout << cube[z][x][y];
                if( y < (Y-1) ){
                    cout << ",";
                }
            }
            cout << endl;
        }
    }

    //
    // ３次元配列の開放
    //
    for(int z = 0; z < Z; z++) {
        for (int x = 0; x < X; x++) {
            delete[] cube[z][x];
        }
        delete[] cube[z];
    }
    delete[] cube;

    return 0;
}