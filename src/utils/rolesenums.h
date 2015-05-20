#ifndef ROLESENUMS_H
#define ROLESENUMS_H


class RolesEnums
{
public:
    RolesEnums();
    ~RolesEnums();
    enum ActionContext {
        FOLDERS_ONLY,EVENTS_ONLY,ALL
    };
    enum PhotoActionContext {
        SINGLE_PHOTO,MULTIPLE_PHOTOS,ANY_PHOTOS,
        SINGLE_EVENT,MULTIPLE_EVENTS,ANY_EVENTS
    };
    enum PhotoOrEvent {
        PHOTO,EVENT
    };
    static const int PHOTO_PATH_PROPERTY;
    static const int PHOTO_OR_EVENT_PROPERTY;
};

#endif // ROLESENUMS_H
