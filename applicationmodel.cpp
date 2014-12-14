#include "applicationmodel.h"

ApplicationModel *ApplicationModel::instance = NULL;

ApplicationModel::ApplicationModel()
{
    cout << "Making app model" << endl;
}

ApplicationModel *ApplicationModel::getApplicationModel() {
    if(!instance) {
        instance = new ApplicationModel();
    }
    return instance;
}
