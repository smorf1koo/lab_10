#include <iostream>

template<typename T>
class MyDeck{
private:
    // узел
    struct Node{
        T data;
        Node* prev_index;
        Node* next_index;
        Node(T data, Node* prev_index = nullptr, Node* next_index = nullptr) :
        data(data), prev_index(prev_index), next_index(next_index){}
    };
    size_t _size;
    Node* _head; // указатель на начало очереди
    Node* _tail; // указатель на конец очереди
public:
    MyDeck():_size(0), _head(nullptr), _tail(nullptr){}

    ~MyDeck(){
        while (_head != nullptr){
            Node* temp = _head;
            _head = _head->next_index;
            delete temp;
        }
    }

    void push_back(const T& value){
        Node* node = new Node(value, _tail, nullptr);
        if (_tail != nullptr) _tail->next_index = node;
        _tail = node;
        if (_head == nullptr) _head = node;
        _size++;
    }

    void push_front(const T& value){
        Node* node = new Node(value, nullptr, _head);
        if (_head != nullptr) _head->prev_index = node;
        _head = node;
        if (_tail == nullptr) _tail = node;
        _size++;
    }

    void pop_back(){
        if (_tail == nullptr) return;
        Node* temp = _tail;
        _tail = _tail->prev_index;
        if (_tail != nullptr) {
            _tail->next_index = nullptr;
        } else {
            _head = nullptr;
        }
        delete temp;
        _size--;
    }
    void pop_front(){
        if (_head == nullptr) return;
        Node* temp = _head;
        _head = _head->next_index;
        if (_head != nullptr) {
            _head->prev_index = nullptr;
        } else {
            _tail = nullptr;
        }
        delete temp;
        _size--;
    }
    size_t size(){return _size;}

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const MyDeck<U>& deck);
};
template<typename T>
std::ostream& operator<<(std::ostream& os, const MyDeck<T>& deck) {
    typename MyDeck<T>::Node* current = deck._head;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next_index;
    }
    return os;
}
int main() {
    MyDeck<int> deck;
    deck.push_back(1);
    deck.push_front(2);
    deck.push_back(3);

    std::cout << "Size: " << deck.size() << std::endl;

    deck.pop_front();
    deck.pop_back();

    std::cout << "Size: " << deck.size() << std::endl;
    std::cout << deck;
    return 0;
}
