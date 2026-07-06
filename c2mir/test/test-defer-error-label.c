// Test label on defer should error
int main() {
    mylabel:
    defer { }
    return 0;
}
