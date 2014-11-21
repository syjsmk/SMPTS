

typedef struct InnerTimer {


    char* (*getTime)(struct InnerTimer *self);

} InnerTimer;

InnerTimer* newInnerTimer();
char* getTime(struct InnerTimer *self);