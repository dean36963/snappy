#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <iostream>

using namespace std;

class ApplicationModel
{
protected:
    ApplicationModel();
public:
    static ApplicationModel* getApplicationModel();

private:
    static ApplicationModel *instance;
};

#endif // APPLICATIONMODEL_H
