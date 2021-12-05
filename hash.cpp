
#include "hash.h"
#include "math.h"
HashTable::HashTable(unsigned size, hash_fn hash){
    this->m_hash = hash;
    this->m_table1 = new File[size];
    this->m_table2 = new File[size];
    this->m_size1 = 1;
    m_capacity1 = size;
}

HashTable::~HashTable(){
}

File HashTable::getFile(string name, unsigned int diskBlock){
    for (int i = 0; i < m_size1; i++)
    {
        if (m_table1[i].key() == name and m_table1[i].diskBlock() == diskBlock)
        {
            return m_table1[i];
        }
    }
    
}

bool HashTable::insert(File file){
    if (m_size1<m_capacity1)
    {
        m_table1[m_size1] = file;
        this->m_size1 += 1;
        return true;
    }
    else
    {
        return false;
    }
}

bool HashTable::remove(File file){
    
    return true;
}

float HashTable::lambda(TABLENAME tablename) const {
    return numEntries(tablename)/tableSize(tablename);
}

float HashTable::deletedRatio(TABLENAME tableName) const {
    return m_numDeleted1 / m_size1;
}

void HashTable::dump() const {
    cout << "Dump for table 1: " << endl;
    if (m_table1 != nullptr)
        for (int i = 0; i < m_capacity1; i++) {
            cout << "[" << i << "] : " << m_table1[i] << endl;
        }
    cout << "Dump for table 2: " << endl;
    if (m_table2 != nullptr)
        for (int i = 0; i < m_capacity2; i++) {
            cout << "[" << i << "] : " << m_table2[i] << endl;
        }
}

bool HashTable::isPrime(int number){
    bool result = true;
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) {
            result = false;
            break;
        }
    }
    return result;
}

int HashTable::findNextPrime(int current){
    //we always stay within the range [MINPRIME-MAXPRIME]
    //the smallest prime starts at MINPRIME
    if (current < MINPRIME) current = MINPRIME-1;
    for (int i=current; i<MAXPRIME; i++) { 
        for (int j=2; j*j<=i; j++) {
            if (i % j == 0) 
                break;
            else if (j+1 > sqrt(i) && i != current) {
                return i;
            }
        }
    }
    //if a user tries to go over MAXPRIME
    return MAXPRIME;
}