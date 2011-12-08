// http://www.douban.com/group/topic/23895216/
// 在当前目录中存在文件名为"case1.in"（其中case后为数字1，不是字母l，写错提交后会判错）的文本文件，
// 其内容为一篇英文文章（以EOF作为结束标志）。现要求读取该文本文件内容，统计文章中每个单词出现的次数，
// 并输出出现次数最多的前5个单词及其出现次数（按出现次数由多到少的顺序输出，次数相同时按字典顺序输出，
// 不足5个单词时，按序输出全部单词）。程序中注意如下细节：
// （1） 空格、标点符号与回车符起到分隔单词的作用。
// （2） 文章一行的末尾可能有连字符，出现连字符时，该行最末的字符串与下行最先出现的字符串构一个单词；
// （3） 名词缩写算一个单词；
// （4） 数字不算单词；
// （5） 单词不区分大小写；
// （6） 输出时单词全使用小写； 

#include <iostream>
#include <fstream>
#include <map>

#include <cstdio>
#include <cassert>

void gen_word_cnt_map(const char* filename, std::map<std::string,int>& cntmap) {
    std::ifstream ifs(filename, std::ifstream::in);
    std::string word;
    while (ifs.good()) {
        int ch = tolower(ifs.get());
        // fprintf(stderr, "\033[37m %X\033[0m", ch);
        if (islower(ch)) {
            word += ch;
        } else {
            if ((ch == '-') && (ifs.peek() == '\n')) {
                ifs.get();      // skip "-\n"
                // fprintf(stderr, "\033[31m*\033[0m");
                continue;
            }
            if (word.size()) {
                fprintf(stderr, "%s ", word.c_str());
                ++cntmap[word];
                word.clear();
            }
        }
    }
    ifs.close();
    fprintf(stderr, "\n");
}

void get_by_freq(std::map<std::string,int>& cntmap, int threshold) {
    std::multimap<int,std::string> rmap;
    for (std::map<std::string,int>::iterator it = cntmap.begin(); it != cntmap.end(); ++it)
        rmap.insert(std::make_pair(it->second, it->first));

    int left_cnt = threshold;
    for (std::multimap<int,std::string>::reverse_iterator it = rmap.rbegin(); it != rmap.rend(); ++it) {
        if (left_cnt-- == 0)
            break;
        printf("%s : %d\n", it->second.c_str(), it->first);
    }
}

int main(int argc, char* argv[]) {
    std::map<std::string,int> cntmap;
    if (argc == 1)
        gen_word_cnt_map("case1.in", cntmap);
    else
        gen_word_cnt_map(argv[1], cntmap);
    get_by_freq(cntmap, 5);
    return 0;
}
