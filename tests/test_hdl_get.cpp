#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "test_resources.h"
#include "hdl_list.h"

BOOST_AUTO_TEST_CASE(hdl_list_get_by_key)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_insert (L, k1, source1);
    hdl_insert (L, k2, source2);
    hdl_insert (L, k3, source3);
    hdl_insert (L, k4, source4);

    //find k3 and cmpare with source3
    const hdl_element *e1 = hdl_get_element_by_key(L, k4);

    BOOST_CHECK (e1 != NULL);
    BOOST_CHECK (strcmp( (const char*)e1->value, source4) == 0);

    //try to find sth not present
    const hdl_element *e2 = hdl_get_element_by_key(L, k6);
    BOOST_CHECK (e2 == NULL);

    hdl_destroy (&L);
    BOOST_CHECK (L == NULL);

}

BOOST_AUTO_TEST_CASE(hdl_list_get_by_hash)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_insert (L, k1, source1);
    hdl_insert (L, k2, source2);
    hdl_insert (L, k3, source3);
    hdl_insert (L, k4, source4);

    //find k3 and cmpare with source3
    const unsigned int hash4 = RSHash(k4, strlen(k4));
    const hdl_element *e1 = hdl_get_element_by_hash(L, hash4);

    BOOST_CHECK (e1 != NULL);
    BOOST_CHECK (strcmp( (const char*)e1->value, source4) == 0);

    //try to find sth not present
    const unsigned int hash6 = RSHash(k6, strlen(k6));
    const hdl_element *e2 = hdl_get_element_by_hash(L, hash6);
    BOOST_CHECK (e2 == NULL);

    hdl_destroy (&L);
    BOOST_CHECK (L == NULL);

}

BOOST_AUTO_TEST_CASE(hdl_list_get_value_by_key)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_insert (L, k1, source1);
    hdl_insert (L, k2, source2);
    hdl_insert (L, k3, source3);
    hdl_insert (L, k4, source4);

    //find k3 and cmpare with source3
    const char* e1 = (const char*) hdl_get_value_by_key(L, k4);

    BOOST_CHECK (e1 != NULL);
    BOOST_CHECK (strcmp (e1, source4) == 0);

    //try to find sth not present
    const char* e2 = (const char*) hdl_get_value_by_key(L, k6);
    BOOST_CHECK (e2 == NULL);

    hdl_destroy (&L);
    BOOST_CHECK (L == NULL);
}

BOOST_AUTO_TEST_CASE(hdl_list_get_value_by_hash)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_insert (L, k1, source1);
    hdl_insert (L, k2, source2);
    hdl_insert (L, k3, source3);
    hdl_insert (L, k4, source4);

    //find k3 and cmpare with source3
    const unsigned int hash4 = RSHash(k4, strlen(k4));
    const char *e1 = (const char*) hdl_get_value_by_hash(L, hash4);

    BOOST_CHECK (e1 != NULL);
    BOOST_CHECK (strcmp( e1, source4) == 0);

    //try to find sth not present
    const unsigned int hash6 = RSHash(k6, strlen(k6));
    const char *e2 = (const char*) hdl_get_value_by_hash(L, hash6);
    BOOST_CHECK (e2 == NULL);

    hdl_destroy (&L);
    BOOST_CHECK (L == NULL);
}
