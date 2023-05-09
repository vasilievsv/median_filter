#pragma once

#include <cstdio>
#include <unistd.h>
#include <math.h>
#include "LinkedList/LinkedList.h"

class BaseFilter
{
    
};

template<typename type>
class MedianFilter
{
    typedef struct
    {
        type value;
        void *nextAge;
        void *nextValue;
        void *prevValue;
    }MedianNode;

    MedianNode *m_ageHead;
    MedianNode *m_valueHead;
    MedianNode *m_medianHead;

    LinkedList<MedianNode*> _list;
public:
    MedianFilter();
    MedianFilter(int amount_elem)
    {
        ResizeBuffer(amount_elem);
        Init(amount_elem, 0);
    }

    virtual ~MedianFilter()
    {
        _list.clear();
    };

    bool ResizeBuffer(int len)
    {
        _list.clear();

        for (int i = 0; i < len; i++)
            if (_list.add(new MedianNode) == false)
                goto fail;

        return true;
    fail:
        return false;
    }

    bool Init(int n, type init_value)
    {
        for (int i = 0; i < n; i++)
        {
            auto key = (i + 1) % n;
            auto node = _list[i];
            auto node_next = _list[(i + 1) % n];

            node->value = init_value;
            node->nextAge = _list[key];
            node->nextValue = _list[key];
            node_next->prevValue = _list[i];
        }

        m_ageHead = _list[0];
        m_valueHead = _list[0];
        m_medianHead = _list[n / 2];

        return true;
    }

    type Insert(type value)
    {
        int i;
        MedianNode *newNode, *it;

        if (m_ageHead == m_valueHead)
        {
            m_valueHead = (MedianNode *)m_valueHead->nextValue;
        }

        if ((m_ageHead == m_medianHead) || (m_ageHead->value > m_medianHead->value))
        {
            m_medianHead = (MedianNode *)m_medianHead->prevValue;
        }

        newNode = (MedianNode *)m_ageHead;
        newNode->value = value;

        ((MedianNode *)m_ageHead->nextValue)->prevValue = (MedianNode *)m_ageHead->prevValue;
        ((MedianNode *)m_ageHead->prevValue)->nextValue = (MedianNode *)m_ageHead->nextValue;
        m_ageHead = (MedianNode *)m_ageHead->nextAge;

        it = m_valueHead;
        for (i = 0; i < _list.size() - 1; i++)
        {
            if (value < it->value)
            {
                if (i == 0)
                {
                    m_valueHead = newNode;
                }
                break;
            }
            it = (MedianNode *)it->nextValue;
        }

        ((MedianNode *)it->prevValue)->nextValue = newNode;
        ((MedianNode *)newNode)->prevValue = it->prevValue;
        it->prevValue = newNode;
        newNode->nextValue = it;

        if (i >= (_list.size() / 2))
        {
            m_medianHead = (MedianNode *)m_medianHead->nextValue;
        }

        return m_medianHead->value;
    }
};
