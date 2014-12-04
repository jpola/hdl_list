#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "test_resources.h"
#include "hdl_list.h"

BOOST_AUTO_TEST_CASE(hdl_list_delete_by_key)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_push_front (L, k1, source1);
    hdl_push_front (L, k2, source2);
    hdl_push_front (L, k3, source3);

    BOOST_CHECK (L->count == 3);

    hdl_delete_element_by_key(L, k2);

    //we shall not find k2 anymore in the list;
    BOOST_CHECK (L->count == 2);
    BOOST_CHECK (hdl_find_by_key(L, k2) == NULL);

    hdl_destroy(&L);
    BOOST_CHECK (L == NULL);
}

BOOST_AUTO_TEST_CASE(hdl_list_delete_by_hash)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_push_front (L, k1, source1);
    hdl_push_front (L, k2, source2);
    hdl_push_front (L, k3, source3);

    BOOST_CHECK (L->count == 3);

    unsigned int h = RSHash(k2, strlen(k2));
    hdl_delete_element_by_hash(L, h);

    //we shall not find k2 anymore in the list;
    BOOST_CHECK (L->count == 2);
    BOOST_CHECK (hdl_find_by_hash(L, h) == NULL);

    hdl_destroy(&L);
    BOOST_CHECK (L == NULL);

}

BOOST_AUTO_TEST_CASE(hdl_list_delete_element)
{

    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_push_front (L, k1, source1);
    hdl_push_front (L, k2, source2);
    hdl_push_front (L, k3, source3);

    BOOST_CHECK (L->count == 3);

    hdl_element *e = hdl_find_by_key(L, k2);

    hdl_delete_element(L, &e);

    BOOST_CHECK(e == NULL);
    BOOST_CHECK (L->count == 2);


    hdl_destroy(&L);
    BOOST_CHECK (L == NULL);


}
