/*
 * ---------------------------------------------------
 * Func.hpp
 *
 * Author: Thomas Choquet <thomas.publique@icloud.com>
 * Date: 2024/01/11 16:26:50
 * ---------------------------------------------------
 */

#ifndef FUNC_HPP
# define FUNC_HPP

#include "UtilsCPP/SharedPtr.hpp"

namespace utils
{

template <typename>
class Func;

template<typename ReturnValue, typename ... Args>
class Func<ReturnValue(Args...)> 
{
private:
    class ICallable 
    {
    public:
        virtual ReturnValue call(Args...) const = 0;
        virtual ~ICallable() = default;
    };

    template<typename F>
    class CallableF : public ICallable
    {
    public:
        CallableF()                 = delete;
        CallableF(const CallableF&) = delete;
        CallableF(CallableF&&)      = delete;

        CallableF(const F& f) : m_f(f) {}
        CallableF(F&& f) : m_f((F&&)f) {}

        inline ReturnValue call(Args... args) const override { return m_f(args...); }

        ~CallableF() override = default;

    private:
        F m_f;
    };

    class CallablePTR : public ICallable
    {
    public:
        CallablePTR()                   = delete;
        CallablePTR(const CallablePTR&) = delete;
        CallablePTR(CallablePTR&&)      = delete;

        CallablePTR(ReturnValue (*f)(Args... args)) : m_f(f) {}

        inline ReturnValue call(Args... args) const override { return m_f(args...); }

        ~CallablePTR() override = default;

    private:
        ReturnValue (*m_f)(Args... args);
    };

    template<typename Object>
    class CallableMEM : public ICallable
    {
    public:
        CallableMEM()                   = delete;
        CallableMEM(const CallableMEM&) = delete;
        CallableMEM(CallableMEM&&)      = delete;

        CallableMEM(Object& obj, ReturnValue (Object::*f)(Args... args)) : m_obj(obj), m_f(f) {}

        inline ReturnValue call(Args... args) const override { return (m_obj.*m_f)(args...); }

        ~CallableMEM() override = default;

    private:
        Object& m_obj;
        ReturnValue (Object::*m_f)(Args... args);
    };

public:
    Func()               = default;
    Func(const Func& cp) = default;
    Func(Func&& mv)      = default;

    template <typename F>
    Func(const F& f) : m_callable(new CallableF<F>(f))
    {
    }

    Func(ReturnValue (*f)(Args... args)) : m_callable(new CallablePTR(f))
    {
    }

    template<typename Object>
    Func(Object& obj, ReturnValue (Object::*f)(Args... args)) : m_callable(new CallableMEM<Object>(obj, f))
    {
    }

    ~Func() = default;

private:
    SharedPtr<ICallable> m_callable;

public:
    Func& operator = (const Func& rhs) = default;
    Func& operator = (Func&& rhs) = default;

    inline ReturnValue operator () (Args... args) const { return m_callable->call(args...); }
    inline operator bool () const { return (bool)m_callable; }
};

}

#endif // FUNC_HPP