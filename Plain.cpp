#include <bits/stdc++.h>
using namespace std;

#define FIELD_PRIME 11;

// FIELD OPERATIONS //

int FIELD_ADD(int A, int B) {
    return A + B % FIELD_PRIME;
}

int FIELD_MULT(int A, int B) {
    return A * B % FIELD_PRIME;
}

// ---------------- //

vector<int>generateRandomPoly(int k) {
    vector<int> arr;
    for (int i=0; i<k ;i++) {
        arr.push_back(rand()%100);
    }
    return arr;
}

vector<int> generateShares (vector<int>poly) {
    vector<int> ans;
    int order = poly.size() - 1;
    for (int i=0; i<poly.size(); i++) {
        int sum = 0;
        for (int j=0; j<poly.size(); j++) {
            sum += poly[j] * pow(i, order-j);
        }
        ans.push_back(sum);
    }
    return ans;
}

double generateLagrangeConstant(int shareVal, int shareSize, int shareNo) {
    int numerator = 1, denominator = 1;
    for (int i=0; i<shareSize; i++) {
        if (i != shareNo) {
            numerator *= -(i);
            denominator *= (shareNo - i);
        }
    }
    double con = (numerator/denominator)*shareVal;
    return con;
}

double verify(vector<int>shares) {
    double ans = 0;
    for (int i=0 ;i<3; i++) {
        double lagrangeConstant = generateLagrangeConstant(shares[i], shares.size(), i);
        ans += lagrangeConstant;
    }
    return ans;
}

int main() {
    srand(time(0));
    int k;
    cout << "no of shares: ";
    cin >> k;
    cout << "poly: [ ";
    vector<int> poly = generateRandomPoly(k);
    for (int i=0; i<poly.size(); i++) {
        cout << poly[i] << " ";
    }
    cout << "]" << endl;
    cout << "secret: " << poly[poly.size()-1] << endl;
    vector<int> shares = generateShares(poly);
    double verifiedVal = verify(shares);
    if (verifiedVal == double(poly[poly.size()-1])) {
        cout << "verified: " << verifiedVal << endl;
    }
}