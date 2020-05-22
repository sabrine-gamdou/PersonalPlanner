#ifndef DAO_H
#define DAO_H

template <typename T>

class DAO{
public:

    virtual ~DAO() = 0;
    virtual bool create(T t) = 0;
    virtual T read() = 0;
    virtual bool update(T t) = 0;
    virtual bool delete_(T t) = 0;
};

#endif // DAO_H
