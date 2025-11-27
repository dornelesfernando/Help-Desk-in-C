#ifndef STRUCTS_H
#define STRUCTS_H

    #include <time.h>
    
    typedef struct {
        int call_id;
        int is_logged_in;
        int last_opened_call_id;
        int returned_call_id_aux;
        int input_status;
        int returned_call_id;
        int priority_filter;
        int status_filter;
        int request_log;
    
        char log_message[128];
    } MainParams;
    
    // Define the status
    typedef enum {
        ABERTO,
        EM_ANDAMENTO,
        RESOLVIDO,
        CANCELADO,
        SUSPENSO
    } StatusEnum;
    
    // Define the priority
    typedef enum {
        BAIXA,
        MEDIA,
        ALTA,
        URGENTE,
        RETORNADO
    } PriorityEnum;
    
    // Define items
    typedef enum {
        NONE,
        MOUSE,
        KEYBOARD,
        CABO_HDMI,
        MONITOR,
        IMPRESSORA,
        NOTEBOOK,
        CABO_REDE,
        WEBCAM,
        HEADSET
    } ItemsEnum;
    
    typedef struct {
        // --- Identificação ---
        int id;
    
        // --- Quem ---
        char name[100];
        char email[100];
    
        // --- O Quê ---
        char title[150];
        char desc[1024];
        ItemsEnum item;
        int qtd_item;
    
        // --- Como ---
        StatusEnum status;
        PriorityEnum priority;
        char name_func[100];
    
        // --- Quando ---
        time_t created_at;
        time_t updated_at;
        time_t data_fechamento;
    
        // --- Resolução ---
        char solution[1024];
    } Call;
    
    typedef struct {
        Call *data;
        int capacity;
        int size;
    } CallHeap;
    
    typedef struct {
        Call *data;  
        int capacity;
        int size;
        int front;  
        int tail;       
    } CallFIFO;
    
    typedef struct CallNode {
        Call *data;
        struct CallNode *next;
        struct CallNode *prev;
    } CallNode;
    
    typedef struct {
        CallNode *head;
        CallNode *tail;
        int size;
    } CallService;
    
    typedef struct ArvNo {
        char name[100];
        int qtd;
        CallService *datas;
        struct ArvNo *right;
        struct ArvNo *left;
    } ArvNo;
    
    typedef struct Arv {
        ArvNo *raiz; 
    } Arv;

#endif // STRUCTS_H
