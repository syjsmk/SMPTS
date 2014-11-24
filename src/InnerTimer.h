

typedef struct InnerTimer {


    void (*getTime)(struct InnerTimer *self, char *buffer);

} InnerTimer;

InnerTimer* newInnerTimer();
void getTime(struct InnerTimer *self, char *buffer);