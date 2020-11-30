#include <iostream>
using namespace std;

// SingletonLazy
class SingletonLazy
{
protected:
    SingletonLazy(){}
private:
    static SingletonLazy* p;
public:
    static SingletonLazy* instance();
};
SingletonLazy* SingletonLazy::p = NULL;
SingletonLazy* SingletonLazy::instance()
{
    if (p == NULL)
        p = new SingletonLazy();
    return p;
}

// SingletonLazyLock
class SingletonLazyLock
{
protected:
    SingletonLazyLock()
    {
        pthread_mutex_init(&mutex, NULL);
    }
private:
    static SingletonLazyLock* p;
public:
    static pthread_mutex_t mutex;
    static SingletonLazyLock* instance();
};

pthread_mutex_t SingletonLazyLock::mutex;
SingletonLazyLock* SingletonLazyLock::p = NULL;
SingletonLazyLock* SingletonLazyLock::instance()
{
    if (p == NULL)
    {
        pthread_mutex_lock(&mutex);
        if (p == NULL)
            p = new SingletonLazyLock();
        pthread_mutex_unlock(&mutex);
    }
    return p;
}


// SingletonLazyLockNoPtr
class SingletonLazyLockNoPtr
{
protected:
    SingletonLazyLockNoPtr()
    {
        pthread_mutex_init(&mutex_noptr, NULL);
    }
public:
    static pthread_mutex_t mutex_noptr;
    static SingletonLazyLockNoPtr* instance();
    int a;
};

pthread_mutex_t SingletonLazyLockNoPtr::mutex_noptr;
SingletonLazyLockNoPtr* SingletonLazyLockNoPtr::instance()
{
    pthread_mutex_lock(&mutex_noptr);
    static SingletonLazyLockNoPtr obj;
    pthread_mutex_unlock(&mutex_noptr);
    return &obj;
}

// SingletonHungry
class SingletonHungry
{
protected:
    SingletonHungry()
    {}
private:
    static SingletonHungry* p;
public:
    static SingletonHungry* instance();
};
SingletonHungry* SingletonHungry::p = new SingletonHungry();
SingletonHungry* SingletonHungry::instance()
{
    return p;
}

int main() {
    SingletonLazy::instance();
    SingletonLazyLock::instance();
    SingletonLazyLockNoPtr::instance();
    SingletonHungry::instance();
    return 0;
}
