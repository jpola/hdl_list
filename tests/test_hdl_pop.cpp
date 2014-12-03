#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK

#include <boost/test/unit_test.hpp>

#include "test_resources.h"
#include "hdl_list.h"

BOOST_AUTO_TEST_CASE(hdl_list_pop_back)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_push_front (L, k1, source1); //push front causes that this is the last
    hdl_push_front (L, k2, source2);
    hdl_push_front (L, k3, source3);

    BOOST_CHECK (L->count == 3);

    hdl_element* e = hdl_pop_back(L);

    BOOST_CHECK (L->count == 2);

    BOOST_CHECK (strcmp ((char*)e->value, source1) == 0);

    // remember to take care of this element when poped
    // list looses control over it after pop
    free(e);

    hdl_destroy(&L);
    BOOST_CHECK (L == NULL);

}

BOOST_AUTO_TEST_CASE(hdl_list_pop_front)
{
    hdl_list* L = NULL;
    L = hdl_create (false);

    BOOST_CHECK (L != NULL);

    hdl_push_front (L, k1, source1); //push front causes that this is the last
    hdl_push_front (L, k2, source2);
    hdl_push_front (L, k3, source3);

    BOOST_CHECK (L->count == 3);

    hdl_element* e = hdl_pop_front(L);

    BOOST_CHECK (L->count == 2);

    BOOST_CHECK (strcmp ((char*)e->value, source3) == 0);

    // remember to take care of this element when poped
    // list looses control over it after pop
    free(e);

    hdl_destroy(&L);
    BOOST_CHECK (L == NULL);
}
