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
        virtual ICallable* clone() const = 0;
        virtual ~ICallable() = default;
    };

    template<typename F>
    class CallableF : public ICallable
    {
    public:
        CallableF()                 = delete;
        CallableF(const CallableF&) = delete;
        CallableF(CallableF&&)      = delete;

        explicit CallableF(const F& f) : m_f(f) {}
        explicit CallableF(F&& f) : m_f((F&&)f) {}

        inline ReturnValue call(Args... args) const override { return m_f(args...); }
        ICallable* clone() const override { return new CallableF(m_f); } // TODO NOLINT(cppcoreguidelines-owning-memory)

        ~CallableF() override = default;

    private:
        F m_f;

    public:
        CallableF& operator = (const CallableF&) = delete;
        CallableF& operator = (CallableF&&)      = delete;
    };

    class CallablePTR : public ICallable
    {
    public:
        CallablePTR()                   = delete;
        CallablePTR(const CallablePTR&) = delete;
        CallablePTR(CallablePTR&&)      = delete;

        explicit CallablePTR(ReturnValue (*f)(Args... args)) : m_f(f) {}

        inline ReturnValue call(Args... args) const override { return m_f(args...); }
        ICallable* clone() const override { return new CallablePTR(m_f); } // TODO NOLINT(cppcoreguidelines-owning-memory)

        ~CallablePTR() override = default;

    private:
        ReturnValue (*m_f)(Args... args);

    public:
        CallablePTR& operator = (const CallablePTR&) = delete;
        CallablePTR& operator = (CallablePTR&&)      = delete;

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
        ICallable* clone() const override { return new CallableMEM(m_obj, m_f); } // TODO NOLINT(cppcoreguidelines-owning-memory)

        ~CallableMEM() override = default;

    private:
        Object& m_obj;
        ReturnValue (Object::*m_f)(Args... args);

    public:
        CallableMEM& operator = (const CallableMEM&) = delete;
        CallableMEM& operator = (CallableMEM&&)      = delete;
    };

public:
    Func() = default;

    Func(const Func& cp) : m_callable(cp.m_callable->clone())
    {
    }

    Func(Func&& mv) noexcept : m_callable(mv.m_callable)
    {
        mv.m_callable = nullptr;
    }

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

    ~Func()
    {
        delete m_callable;
    }

private:
    ICallable* m_callable = nullptr; // TODO use unique pointer ? (maybe a shared pointer)

public:
    inline ReturnValue operator () (Args... args) const { return m_callable->call(args...); }

    Func& operator = (const Func& rhs)
    {
        if (&rhs != this)
        {
            delete m_callable;
            if (rhs.m_callable)
                m_callable = rhs.m_callable->clone();
            else
                m_callable = nullptr;
        }
        return *this;
    }

    Func& operator = (Func&& rhs) noexcept
    {
        if (&rhs != this)
        {
            delete m_callable;
            m_callable = rhs.m_callable;
            rhs.m_callable = nullptr;
        }
        return *this;
    }

    inline operator bool () const { return m_callable != nullptr; }
};

}

#endif // FUNC_HPP