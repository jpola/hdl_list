/**
    lets try to implement a hash table with  keys  of type const char*
    which return const char* value;
*/

#include "hdl_list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


hdl_list* hdl_create (bool cl_type)
{
    hdl_list* list = malloc (sizeof (hdl_list));

    if (list == NULL) return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->cl_type = cl_type;
    list->count = 0;

    return list;
}

size_t hdl_size (const hdl_list *list)
{
    return list->count;
}

/* FIND FUNCTION SECTION */

hdl_element* hdl_find_by_hash (const hdl_list *list, const unsigned int hash)
{
    hdl_element *p = list->head;

    //TODO: Wartowinik? chyba nie potrzebny bo to będzie mała lista
    int index = 0;
    while (p && p->hash != hash)
    {
        p = p->next;
    }

    return p;
}

hdl_element* hdl_find_by_key (const hdl_list *list, const char* key)
{
    unsigned int hash = RSHash(key, strlen(key));

    return hdl_find_by_hash(list, hash);
}


/* INSERT FUNCTION SECTION */


// TODO: what should be value void*, const void*??
// TODO: Error handling ?? Jaki sposób;
// Jeżeli wkładam coś do listy to odpowiedzialność spada na listę aby
// element dobrze usunąć
void hdl_push_front(hdl_list *list, const char* key, const void* value)
{
    unsigned int hash = RSHash (key, strlen(key));

    // Chcemy mieć unikalne elementy w liście;
    hdl_element* e = hdl_find_by_hash(list, hash);

    if (e == NULL )  // nie znaleziono elementu o kluczu = key
    {
        e = malloc  (sizeof (hdl_element));     // nie rzutować w C
        e->value = (void*)value;           // przenoszę adres do listy
        e->hash = hash;             // dodajemy identyfikator
        e->prev = NULL;             // pierwszy element w liście nie posiada poprzednika;
        e->next = list->head;     // następny element po pierwszym to głowa
        list->head = e;                // głowa wskazuje na pierwszy element
        list->count++;                // zwiekszamy ilość elementów w liście

        // komunikacja z ogonem
        // jeżeli e posiada następnik np c dodanego elementu to musimy go podłączyć
        // e->next oznacza ze idziemy head->e->c, gdzie c = e->next;
        // gdy wywołujemy prev na elemencie to zbliżamy się do głowy! stąd e->next->prev = e;
        if(e->next)
            e->next->prev = e;
        else
            list->tail = e;     // w przeciwnym razie e jest jedynym elementem w liscie; head i tail wskazuje na e;
    }
#ifndef NDEBUG
    else
    {
        fprintf(stderr, "Key (%s, %u) already exists\n Element will is not added\n", key, hash);
    }
#endif
}

//TODO: Te same pytania co hdl_push_front
void hdl_push_back(hdl_list *list, const char* key, const void* value)
{
    unsigned int hash = RSHash (key, strlen(key));

    hdl_element* e = hdl_find_by_hash(list, hash);

    if (e == NULL )
    {
        e = malloc (sizeof (hdl_element));
        e->value = (void*)value;
        e->hash = hash;
        e->next = NULL;
        e->prev = list->tail;
        list->tail = e;
        list->count++;

        //komunikacja z głową listy symetrycznie do push_front;
        if (e->prev)
            e->prev->next = e;
        else
            list->head = e;

    }
#ifndef NDEBUG
    else
    {
        fprintf(stderr, "Key (%s, %u) already exists\n Element is not added\n",
                key, hash);
    }
#endif
}

void hdl_insert (hdl_list *list, const char* key, const void* value)
{
    hdl_push_back(list, key, value);
}

/** REMOVE / DELETE FUNCTION SECTION */

// helper function used in remove or delete, just properly reorganize
// the list when removing e
static void __hdl_remove_element(hdl_list *list, hdl_element* e)
{
    if (e == NULL) return;      // node not found;

    list->count--;

    // odpowiednie poloczenie elementow w okółe w 2 krokach
    // 1. jesli istniej poprzednik e to w jego polu next
    //    umieszczamy to co bylo w e->prev
    //
    //      head --- c ---  e --- f
    //      e - current element
    //      c := e->prev;
    //      f := e->next;
    //      c->next musi wskazywać na adres f;
    //      f->prev musi wskazywać na adres c;
    if (e->prev) e->prev->next = e->next;
    else list->head = e->next;    // jesli nie ma prev to e był pierwszym
    // elementem i teraz musimy wskazać na f;

    // 2. to samo z ogonem
    if (e->next) e->next->prev = e->prev;
    else list->tail = e->prev;
}

// helper function used to properly free allocated resources
static void __hdl_free_element(hdl_list *list , hdl_element** e)
{
    if(list->cl_type)
    {
#ifndef NDEBUG
        printf("hdl_free_element: removing element by cl_free function\n");
#endif
    }
    else
    {
#ifndef NDEBUG
        printf ("hdl_free_element: removing element by C free() function\n");
#endif
        //if(e->value) free(e->value);
        if(*e)
        {
            free(*e);
        }

        *e = NULL;
    }
}

//delete element from the list, calls free(e) at the end
void hdl_delete_element (hdl_list *list, hdl_element** e)
{
    __hdl_remove_element(list, *e);
    __hdl_free_element(list, e);
}

void hdl_delete_element_by_hash(hdl_list *list, const unsigned int hash)
{
    hdl_element* e = hdl_find_by_hash(list, hash);
    hdl_delete_element(list, &e);
}

void hdl_delete_element_by_key (hdl_list* list, const char* key)
{
    unsigned int hash = RSHash(key, strlen(key));
    hdl_delete_element_by_hash(list, hash);
}


//remove element from the list, does not testroy it
hdl_element* hdl_remove_element (hdl_list *list, hdl_element* e)
{
    __hdl_remove_element(list, e);
    return e;
}

hdl_element* hdl_remove_by_hash (hdl_list *list, const unsigned int hash)
{
    hdl_element* e = hdl_find_by_hash(list, hash);
    return hdl_remove_element(list, e);
}

hdl_element* hdl_remove_by_key (hdl_list *list, const char* key)
{
    unsigned int hash = RSHash(key, strlen(key));
    return hdl_remove_by_hash(list, hash);
}

// TODO: Can we make it better?
void hdl_destroy(hdl_list **list)
{
    if (!(*list)) return;

    hdl_element* e = (*list)->head;
    hdl_element* tmp = NULL;
    while (e)
    {
        tmp = e->next;
        hdl_delete_element(*list, &e);
        e = tmp;
    }
//    for (e = (*list)->head; e != NULL; e = e->next)
//    {
//        hdl_delete_element(*list, &e);
//    }
    free(*list);
    *list = NULL;
}


// jeżeli coś ściągamy z kolejki to kolejka traci nad nim kontrolę
// my musimy zadbać aby odpowienio usunąć go z pamięci
hdl_element* hdl_pop_front (hdl_list *list)
{
    if(list->count)
        return hdl_remove_element(list, list->head);

    return NULL;
}

hdl_element* hdl_pop_back (hdl_list *list)
{
    if(list->count)
        return hdl_remove_element(list, list->tail);

    return NULL;
}


//we just want to read data from hdl_element
const hdl_element* hdl_get_element_by_hash (const hdl_list *list, const unsigned int hash)
{
    return hdl_find_by_hash(list, hash);
}

const hdl_element* hdl_get_element_by_key (const hdl_list *list, const char* key)
{
    const unsigned int hash = RSHash (key, strlen(key));
    return hdl_get_element_by_hash (list, hash);
}

const void* hdl_get_value_by_key(const hdl_list *list, const char* key)
{
    const hdl_element* e = hdl_get_element_by_key(list, key);
    if(e)
        return e->value;
    return NULL;
}

const void* hdl_get_value_by_hash(const hdl_list *list, const unsigned int hash)
{
    const hdl_element* e = hdl_get_element_by_hash(list, hash);
    if(e)
        return e->value;
    return NULL;
}

// diagnostic function
void hdl_print (const hdl_list *list)
{
    hdl_element* e = list->head;

    while (e)
    {
        printf("(%u, %s)\n", e->hash, (const char*)e->value);
        e = e->next;
    }
}


//    int main(int argc, char const *argv[])
//    {
//        printf("HasMap base on strings program START\n");

//        hdl_list* L = hdl_create(false);

//         // This will be autogenerated during build step
//        const char* source1 = "Pierwszy source code";
//        const char* source2 = "Drugi source code";
//        const char* source3 = "Trzeci source code";

//        const char* k1 = "S1";
//        const char* k2 = "S2";
//        const char* k3 = "S3";


//        hdl_push_front(L, k1, source1);
//        hdl_push_front(L, k2, source2);
//        hdl_push_front(L, k3, source3);

//        printf("\nPo dodaniu elementów\n");
//        hdl_print(L);
//        hdl_destroy(L);
//        printf("\nPo usunięciu elementów\n");
//        hdl_print(L);

//        printf("\nPo dodaniu elementów do testów\n");
//        hdl_push_front(L, k1, source1);
//        hdl_push_front(L, k2, source2);
//        hdl_push_front(L, k3, source3);


//        // test for duplicated key;
//        hdl_push_front(L, k3, source2);

//        printf("\nPo dodaniu zduplikowanego elementu\n");
//        hdl_print(L);

//        hdl_remove_by_key(L, k1);
//        printf("\nPo usunięciu %s\n", k1);
//        hdl_print(L);

//        //test na double removal
//        hdl_remove_by_key(L, k1);
//        printf("\nPo usunięciu jeszcze raz %s\n", k1);
//        hdl_print(L);

//        hdl_remove_by_key(L, k2);
//        hdl_remove_by_key(L, k3);
//        printf("\nPo usunięciu wszystkiego\n");
//        hdl_print(L);

//        //remove from empty list;
//        hdl_remove_by_key(L, k2);
//        printf("\nPróba usunięcia z pustej listy\n");
//        hdl_print(L);


//        hdl_destroy(L);
//        free(L);
//        return 0;
//    }
