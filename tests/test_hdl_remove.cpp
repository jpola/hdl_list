#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "test_resources.h"
#include "hdl_list.h"

BOOST_AUTO_TEST_CASE(hdl_list_remove_by_key)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_push_front (L, k1, source1); //push front causes that this is the last
    hdl_push_front (L, k2, source2);
    hdl_push_front (L, k3, source3);

    BOOST_CHECK (L->count == 3);

    hdl_element *e = hdl_remove_by_key(L, k2); //remove element existing in the list
    hdl_element *e1 = hdl_remove_by_key(L, k7);//remve non existing element from the list

    BOOST_CHECK (e1 == NULL);
    BOOST_CHECK (L->count == 2);
    BOOST_CHECK (strcmp((char*)e->value, source2) == 0);

    free(e);
    BOOST_CHECK(e == NULL);

    hdl_destroy(&L);
    BOOST_CHECK (L == NULL);

}


BOOST_AUTO_TEST_CASE(hdl_list_remove_by_hash)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_push_front (L, k1, source1); //push front causes that this is the last
    hdl_push_front (L, k2, source2);
    hdl_push_front (L, k3, source3);

    BOOST_CHECK (L->count == 3);

    unsigned int h1 = RSHash(k2, strlen(k2));
    unsigned int h2 = RSHash(k7, strlen(k7));

    hdl_element *e = hdl_remove_by_hash(L, h1); //remove element existing in the list
    hdl_element *e1 = hdl_remove_by_hash(L, h2);//remve non existing element from the list

    BOOST_CHECK (e1 == NULL);
    BOOST_CHECK (L->count == 2);
    BOOST_CHECK (strcmp((char*)e->value, source2) == 0);

    free(e);
    BOOST_CHECK(e == NULL);

    hdl_destroy(&L);
    BOOST_CHECK (L == NULL);

}
