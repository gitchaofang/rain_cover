#include<iostream>
#include<vector>
#include<unordered_map>
#include<utility>
#include<algorithm>
int binary_search(const std::vector<std::pair<double,double>>& v, const double& targ){
    int left = 0;
    int right = v.size() - 1;
    while(left < right){
        int mid = left + (right - left) / 2;
        if(v[mid].first < targ) left = mid + 1;
        else right = mid;
    }
    return left;
}
int rain_cover(std::vector<double>& input, const double& left, const double& right, const double& wid){
    std::vector<std::pair<double,double>> v;
    for(int i = 0; i < input.size(); ++i){
        if(v.size() == 1 && v[0].first == left && v[0].second == right) return i;
        double head = std::max(left,input[i] - wid);
        double tail = std::min(right,input[i] + wid);
        if(v.empty()){
            v.push_back({head,tail});
            continue;
        }
        int pos = binary_search(v,head);
        if(v[pos].first >= head){
            if(tail >= v[pos].first) v[pos].first = head;
            else v.insert(v.begin() + pos,{head,tail});
            if(pos != 0 && head <= v[pos - 1].second){
                v[pos].first = v[pos - 1].first;
                v.erase(v.begin() + pos - 1);
            }
        }
        else{
            if(head <= v[pos].second) v[pos].second = tail;
            else v.push_back({head,tail});
        }
    }
    return (v.size() == 1 && v[0].first == left && v[0].second == right) ? input.size() : -1;
}

