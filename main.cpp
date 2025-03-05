

#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif
#define _CRTDBG_MAP_ALLOC

#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>


struct HashmapItem {
    const char* key;
    const char* value;
    HashmapItem* next;

    /* TODO: Definieer beide constructors, zorg ervoor dat je memory alloceert op de heap */
    HashmapItem()
        : key(strdup("")), value(strdup("")), next(nullptr) {}
    HashmapItem(const char* k, const char* v){}

    /* TODO: maak deze destructor werkend, en voorzie deze van commentaar. */
    ~HashmapItem() {
    }
};

struct HashMap
{
    HashmapItem** items;
    uint32_t size;
    uint32_t count;

    /* TODO: Definieer de constructor, zorg ervoor dat je memory alloceert op de heap (Hashtable(<type> size)) */
    // Schrijf waar deze comment staat in plaats daarvan een constructor

    // Dit is nodig voor de operator overload zodat we een hashtable kunnen outputten naar de console
    friend std::ostream& operator<<(std::ostream& os, HashMap* hm);

    /* TODO: maak deze destructor werkend, en voorzie deze van commentaar. */
    ~HashMap() {
    }

    /* Je kan deze functie gebruiken om te tellen hoeveel items je daadwerkelijk hebt toegevoegd */
    unsigned int count_existing_items() {
        size_t cnt =0;
        HashmapItem* item;
        for (size_t i = 0; i < size; i++) {
            item = items[i];
            while (item) {
                item = item->next;
                cnt++;
            }
        }
        return cnt;
    }

    /* TODO: Maak deze functie af en voorzie van commentaar */
    void add_item(const char* key, const char* value) {
    }

    /* TODO: Maak deze functie af en voorzie van commentaar */
    HashmapItem* find_item(const char* key) const {
    }

    /* TODO: Maak deze functie af, voorzie van commentaar en bron. Leg uit waarom je voor specifiek deze implementatie van een hashfunctie hebt gekozen
     * https://theartincode.stanis.me/008-djb2/
     * djb2 hash
     */
    size_t hash(const char* str) const {
    }

};

/* Je kan deze functie gebruiken om je hashmap te printen, en als inspiratie later voor hoe je complexere datatypes kan printen */
std::ostream& operator<<(std::ostream& os, HashMap* hm){
    os << "{ " << std::endl;
    int cnt =0;
    for (size_t i = 0; i < hm->size; i++) {
        HashmapItem* item = hm->items[i];
        // item is true wanneer deze niet een nullptr is
        while (item) {
            os << "hash: " << i << ", next: " << cnt << " | k,v: " << item->key << ": " << item->value << ", " << std::endl;
            item = item->next;
            cnt++;
        }
        cnt = 0;
    }
    os << "}" << std::endl;
    return os;
}

/* Testsuite begint hier, je mag deze aanvullen, maar je mag geen tests verwijderen, dit wordt gezien als fraude. */

// Hulpfunctie om een willekeurige string te genereren
std::string generate_random_string(size_t length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);

    std::string result;
    result.reserve(length);
    for (size_t i = 0; i < length; ++i) {
        result += charset[dist(rng)];
    }
    return result;
}

/// @brief Test met n willekeurige keys van lengte √n
/// @param n Aantal items in de hashmap
void test_random_keys(unsigned int n, size_t size) {
    size_t key_length = std::pow(n, 1.0/3.0);  // Lengte van elke key
    std::cout << "keylength: " << key_length << std::endl;
    HashMap* hm = new HashMap(size);  // Groter dan n om te voorkomen dat alles op dezelfde index botst

    auto start_insert = std::chrono::high_resolution_clock::now();
    std::vector<std::string> keys;
    for (unsigned int i = 0; i < n; i++) {
        std::string key = generate_random_string(key_length);
        keys.push_back(key);
        hm->add_item(key.c_str(), "value");
    }
    auto end_insert = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insert_duration = end_insert - start_insert;
    // Start timing for lookups
    auto start_lookup = std::chrono::high_resolution_clock::now();
    // Controleer of alle keys correct zijn toegevoegd
    for (const auto& key : keys) {
        HashmapItem* item = hm->find_item(key.c_str());
        assert(item != nullptr);
        assert(std::strcmp(item->value, "value") == 0);
    }
    auto end_lookup = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> lookup_duration = end_lookup - start_lookup;

    std::cout << "The test 'testRandomKeys' has succeeded!\n";
    std::cout << "Insertion time for " << n << " items: " << insert_duration.count() << " seconds\n";
    std::cout << "Lookup time for " << n << " items: " << lookup_duration.count() << " seconds\n";


    std::cout << "The test 'testRandomKeys' has succeeded!" << std::endl;
    delete hm;
}

/// @brief Tests if the created hash is consistent and not too large
/// @param size The max size of the hash
void test_hash(const unsigned int& size) {
    size_t hashedValue = HashMap(size).hash("apple");
    assert(hashedValue == HashMap(size).hash("apple"));
    assert(hashedValue < size);
}


void test_create_and_delete_hashmap(const unsigned int& size) {
    HashMap* hm = new HashMap(size);

    assert(hm->size == size);
    assert(hm->count == 0);
    for (uint32_t i = 0; i < hm->size; i++) {
        assert(hm->items[i] == nullptr);
    }

    const char* key10     = "Hallo";
    const char* value10   = "Bye";
    const char* key11     = "Hall";
    const char* value11   = "Yooo";
    const char* key12     = "Ball";
    const char* value12   = "Bees";
    const char* key13     = "Boll";
    const char* value13   = "Boos";
    hm->add_item(key10, value10);
    hm->add_item(key11, value11);
    hm->add_item(key12, value12);
    hm->add_item(key13, value13);

    assert(hm->find_item(key10));
    assert(hm->find_item(key11));
    assert(hm->find_item(key12));
    assert(hm->find_item(key13));

    std::vector<const char**> items_copy;
    for (uint32_t i = 0; i < hm->size; i++) {
        HashmapItem* item = hm->items[i];
        while (item) {
            items_copy.push_back(&(item->key));
            item = item->next;
        }
    }

    std::cout << "Before deletion: " << std::endl;
    for (auto i : items_copy) {
        std::cout << *i << " ||| hash: " << hm->hash(*i) << std::endl;
    }

    delete hm;

    std::cout << "After deletion, this should not print the keys or crash (uncomment if it crashes your program, which e.g. will happen on debugging on windows): " << std::endl;
    for (auto i : items_copy) {
        std::cout << i << std::endl;
        std::cout << " !! " << *i << " ||| hash: " << hm->hash(*i) << "" << std::endl;
    }

}

/// @brief Tests if items are added to the hash map correctly
/// @param size The size of the hash map
void test_add_items(const unsigned int& size)
{
    HashMap* hm = new HashMap(size);
    const char* key10   = "Hallo";
    const char* value10 = "Bye";
    const char* key11   = "Hall";
    const char* value11 = "Yooo";
    const char* key12   = "Ball";
    const char* value12 = "Bees";
    hm->add_item(key10, value10);
    hm->add_item(key11, value11);
    hm->add_item(key12, value12);

    //std::cout << hm;

    assert(hm->count_existing_items() == 3);
    assert(hm->count == 3);

    // add a key twice
    hm->add_item(key10, value12);
    assert(hm->count_existing_items() == 3);

    //std::cout << "after adding a key twice" << std::endl;
    //std::cout << hm;

    const char* key1    = "apple";
    const char* value1  = "fruit";
    const char* key2    = "banana";
    const char* value2  = "yellow";
    hm->add_item(key1, value1);
    hm->add_item(key2, value2);

    //std::cout << hm;

    assert(hm->count == 5);
    assert(std::strcmp(hm->find_item(key1)->key, "apple") == 0);
    assert(std::strcmp(hm->find_item(key1)->value, "fruit") == 0);
    assert(std::strcmp(hm->find_item(key2)->key, "banana") == 0);
    assert(std::strcmp(hm->find_item(key2)->value, "yellow") == 0);

    delete hm;
}

/// @brief Tests added items can be found correctly
/// @param size The size of the hash map
void test_find_items(const unsigned int& size)
{
    HashMap* hm = new HashMap(size);
    const char* key1    = "apple";
    const char* value1  = "fruit";
    const char* key2    = "banana";
    const char* value2  = "yellow";
    hm->add_item(key1, value1);
    hm->add_item(key2, value2);

    assert(std::strcmp(hm->find_item(key1)->key, "apple") == 0);
    assert(std::strcmp(hm->find_item(key1)->value, "fruit") == 0);

    //std::cout << hm << std::endl;

    delete hm;
}

/// @brief Tests whether the hashmap handles collisions correctly,
/// by creating a hashmap of size 1 (so collisions always occur)
void test_collision()
{
    HashMap* hm = new HashMap(1);
    const char* key1    = "apple";
    const char* value1  = "fruit";
    const char* key2    = "banana";
    const char* value2  = "yellow";
    hm->add_item(key1, value1);
    hm->add_item(key2, value2);

    //std::cout << "after collision: \n" <<  hm;

    assert(hm->hash(key1) == 0);

    assert(std::strcmp(hm->find_item(key1)->key, "apple") == 0);
    assert(std::strcmp(hm->find_item(key1)->value, "fruit") == 0);
    assert(std::strcmp(hm->find_item(key2)->key, "banana") == 0);
    assert(std::strcmp(hm->find_item(key2)->value, "yellow") == 0);

    delete hm;
}

int main()
{
    const unsigned int size = 4096;
    assert (!(size & (size -1)) && size > 0); // Check if size is a power of 2 (more efficient hashing cause bit operations)
    test_hash(size);
    std::cout << "The test 'testHash' has succeeded!" << std::endl;
    test_create_and_delete_hashmap(3);
    std::cout << "The test 'testCreateAndDeleteHashMap' has succeeded!" << std::endl;
    test_add_items(size);
    std::cout << "The test 'testAddItems' has succeeded!" << std::endl;
    test_find_items(size);
    std::cout << "The test 'testFindItems' has succeeded!" << std::endl;
    test_collision();
    std::cout << "The test 'testCollision' has succeeded!" << std::endl;
    test_random_keys(2<<14, 2<<12);
    test_random_keys(2<<18, 2<<12);
    test_random_keys(2<<18, 2<<17);
    test_random_keys(2<<19, 2<<18);
    return 0;
}