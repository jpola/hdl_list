#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "test_resources.h"
#include "hdl_list.h"

BOOST_AUTO_TEST_CASE(hdl_list_find_by_key)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_insert (L, k1, source1);
    hdl_insert (L, k2, source2);
    hdl_insert (L, k3, source3);
    hdl_insert (L, k4, source4);

    //find k3 and cmpare with source3
    hdl_element *e1 = hdl_find_by_key(L, k3);
    BOOST_CHECK (e1 != NULL);
    BOOST_CHECK (strcmp( (char*)e1->value, source3) == 0);

    //try to find sth not present
    hdl_element *e2 = hdl_find_by_key(L, k6);
    BOOST_CHECK (e2 == NULL);

    hdl_destroy (&L);
    BOOST_CHECK (L == NULL);

}


BOOST_AUTO_TEST_CASE(hdl_list_find_by_hash)
{

    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_insert (L, k1, source1);
    hdl_insert (L, k2, source2);
    hdl_insert (L, k3, source3);
    hdl_insert (L, k4, source4);

    //find k3 and cmpare with source3
    unsigned int hash3 = RSHash(k3, strlen(k3));
    hdl_element *e1 = hdl_find_by_hash(L, hash3);
    BOOST_CHECK (e1 != NULL);
    BOOST_CHECK (strcmp( (char*)e1->value, source3) == 0);

    //try to find sth not present
    unsigned int hash2 = RSHash(k6, strlen(k6));
    hdl_element *e2 = hdl_find_by_hash(L, hash2);
    BOOST_CHECK (e2 == NULL);

    hdl_destroy (&L);
    BOOST_CHECK (L == NULL);

}
