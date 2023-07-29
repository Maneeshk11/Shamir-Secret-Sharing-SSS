#include <bits/stdc++.h>
using namespace std;

#define FIELD_PRIME 11

// FIELD OPERATIONS //

int FIELD_ADD(int A, int B) {
    if (A + B < 0) {
        return FIELD_PRIME + (A + B) % FIELD_PRIME;
    }
    return (A + B) % FIELD_PRIME;
}

int FIELD_MULT(int A, int B) {
    if (A * B < 0) {
        return FIELD_PRIME + (A * B) % FIELD_PRIME;
    }
    return (A * B) % FIELD_PRIME;
}

int FIELD_DIV(int A, int B) {
    int ans = pow(B, FIELD_PRIME-2);
    ans = ans%FIELD_PRIME;
    if (A / B < 0) {
        return FIELD_PRIME + A * (ans)%FIELD_PRIME;
    }
    return A * (ans)%FIELD_PRIME;
}

int FIELD_SUB(int A, int B) {
    if ( A - B < 0) {
        return FIELD_PRIME + (A - B) % FIELD_PRIME;
    }
    return (A - B) % FIELD_PRIME;
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
    int order = poly.size() - 1 ;
    for (int i=0; i<poly.size(); i++) {
        int sum = 0;
        for (int j=0; j<poly.size(); j++) {
            sum += poly[j] * pow(i+1, order-j);
        }
        ans.push_back(sum);
    }
    return ans;
}

vector<int> generateFieldShares (vector<int>shares) {
    vector<int> fieldShares;
    for (int i=0; i<shares.size(); i++) {
        fieldShares.push_back(shares[i]%FIELD_PRIME);
    }
    return fieldShares;
}

int generateLagrangeConstant(int shareVal, int shareSize, int shareNo) {
    int numerator = 1, denominator = 1;
    for (int i=0; i<shareSize; i++) {
        if (i+1 != shareNo) {
            numerator = FIELD_MULT(numerator, FIELD_SUB(0, i+1));
            denominator = FIELD_MULT(denominator, FIELD_SUB(shareNo, i+1));
        }
    }
    numerator = FIELD_MULT(numerator, shareVal);
    int con = FIELD_DIV(numerator, denominator);
    return con;
}

int verify(vector<int>fieldShares) {
    int ans = 0;
    for (int i=0 ;i<fieldShares.size(); i++) {
        int lagrangeConstant = generateLagrangeConstant(fieldShares[i], fieldShares.size(), i+1);
        ans = FIELD_ADD(ans, lagrangeConstant);
    }
    return ans;
}

int main() {
    srand(time(0));
    int k;
    cout << "no of shares: ";
    cin >> k;
    vector<int> poly = generateRandomPoly(k);
    cout << "poly: [ ";
    for (int i=0; i<poly.size(); i++) {
        cout << poly[i] << " ";
    }
    cout << "]" << endl;
    cout << "secret: " << poly[poly.size()-1] << endl;
    cout << "Field secret: " << poly[poly.size()-1]%FIELD_PRIME << endl;
    vector<int> shares = generateShares(poly);
    vector<int> fieldShares = generateFieldShares(shares);
    int verifiedVal = verify(fieldShares);
    if (verifiedVal == int(poly[poly.size()-1]%FIELD_PRIME)) {
        cout << "verified: " << verifiedVal << endl;
    }
    else {
        cout << "wrong: " << verifiedVal << endl;
    }
}