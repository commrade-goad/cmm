// Test goto with defer should error
int main() {
    {
        defer { }
        goto end;
    }
end:
    return 0;
}
