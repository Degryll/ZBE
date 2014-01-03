
class ClaseTest {
public:
    ClaseTest(int value = 0) : n(value) {}

    int getValue() {return (n);}
    void setValue(int value) {this->n = value;}

private:
    int n;
};
