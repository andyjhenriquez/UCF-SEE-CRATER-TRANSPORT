/*
 * DO NOT EDIT!
 * 
 * Automatically generated source code by Pitch Developer Studio
 * Licensed to Roberto Cedeno, SEE, Project Edition
 *
 * Copyright (C) 2006-2023 Pitch Technologies AB. All rights reserved.
 * Use is subject to license terms.
 */
#ifndef DEVELOPER_STUDIO_CACHE_H
#define DEVELOPER_STUDIO_CACHE_H

/* Copyright (c) 2010-2011, Tim Day <timday@timday.com>

Permission to use, copy, modify, and/or distribute this software for any
purpose with or without fee is hereby granted, provided that the above
copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE. */

// Modified to use std::map, std::function, change size, set function, clear,
// only add keys if valid value, add and remove, evict in FIFO order

#include <cassert>
#include <list>
#include <map>
#include <functional>

namespace LunarSimulation {

template <
    typename K,
    typename V
> class Cache
{
public:

    typedef K key_type;
    typedef V value_type;

    // Key access history, most recent at back
    typedef std::list<key_type> key_tracker_type;

    // Key to value and key history iterator
    typedef std::map<
        key_type,
        std::pair<
        value_type,
        typename key_tracker_type::iterator
        >
    > key_to_value_type;

    // Constructor specifies the cached function and
    // the maximum number of records to be stored
    Cache()
        :_capacity(1)
    {}

    void set_function(const std::function<value_type(const key_type&)>& f) {
        _fn = f;
    }

    bool remove(const key_type& k) {
        const typename key_to_value_type::iterator it
            =_key_to_value.find(k);

        if (it !=_key_to_value.end()) {
            _key_to_value.erase(it);
            _key_tracker.remove(k);

            return true;
        } else {
            return false;
        }
    }

    void clear() {
        _key_tracker.clear();
        _key_to_value.clear();
        _capacity = 1;
    }

    // Obtain value of the cached function for k
    value_type operator()(const key_type& k, size_t capacity) {
        if (capacity > _capacity) {
            _capacity = capacity;
        }
        return operator()(k);
    }

    value_type operator()(const key_type& k, const value_type& v, size_t capacity) {
        if (capacity > _capacity) {
            _capacity = capacity;
        }

        remove(k);

        if (v) {
            insert(k,v);
        }

        return v;
    }

    value_type operator()(const key_type& k) {

        // Attempt to find existing record
        const typename key_to_value_type::iterator it
            =_key_to_value.find(k);

        if (it==_key_to_value.end()) {

            // We don't have it:

            // Evaluate function and create new record
            const value_type v=_fn(k);
            if (v) {
                insert(k,v);
            }

            // Return the freshly computed value
            return v;

        } else {

            // We do have it:

            // Return the retrieved value
            return (*it).second.first;
        }
    }

    // Obtain the cached keys, most recently used element
    // at head, least recently used at tail.
    // This method is provided purely to support testing.
    template <typename IT> void get_keys(IT dst) const {
        typename key_tracker_type::const_reverse_iterator src
            =_key_tracker.rbegin();
        while (src!=_key_tracker.rend()) {
            *dst++ = *src++;
        }
    }

private:

    // Record a fresh key-value pair in the cache
    void insert(const key_type& k,const value_type& v) {

        // Method is only called on cache misses
        assert(_key_to_value.find(k)==_key_to_value.end());

        // Make space if necessary
        if (_key_to_value.size()==_capacity)
            evict();

        // Record k as most-recently-used key
        typename key_tracker_type::iterator it
            =_key_tracker.insert(_key_tracker.end(),k);

        // Create the key-value entry,
        // linked to the usage record.
        _key_to_value.insert(
            std::make_pair(
            k,
            std::make_pair(v,it)
            )
            );
        // No need to check return,
        // given previous assert.
    }

    // Purge the least-recently-used element in the cache
    void evict() {

        // Assert method is never called when cache is empty
        assert(!_key_tracker.empty());

        // Identify least recently used key
        const typename key_to_value_type::iterator it
            =_key_to_value.find(_key_tracker.front());
        assert(it!=_key_to_value.end());

        // Erase both elements to completely purge record
        _key_to_value.erase(it);
        _key_tracker.pop_front();
    }

    // The function to be cached
    std::function<value_type(const key_type&)> _fn;

    // Maximum number of key-value pairs to be retained
    size_t _capacity;

    // Key access history
    key_tracker_type _key_tracker;

    // Key-to-value lookup
    key_to_value_type _key_to_value;
};
}

#endif
