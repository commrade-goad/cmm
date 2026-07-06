// Test defer as if body without braces should error
int main() {
    if (1)
        defer { }
    return 0;
}
