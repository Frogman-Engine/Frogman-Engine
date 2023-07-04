#include "../mutex.hpp"
// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.


FE::mutex::mutex() noexcept : m_is_locked(false)
#if _WINDOWS_64BIT_OS_ == 1
, m_mutex( CreateMutex(NULL, FALSE, NULL) )
#endif
{
#if _LINUX_64BIT_OS_ == 1
    pthread_mutex_init(&(this->m_mutex), nullptr);
#endif
}

FE::mutex::~mutex() noexcept
{
    FE_ASSERT(this->m_is_locked.load(std::memory_order_acquire) == true, "CRITICAL ERROR: mutex is still locked", _EXCEPTION_ORIGIN_);

#if _WINDOWS_64BIT_OS_ == 1
    CloseHandle(this->m_mutex);
#elif _LINUX_64BIT_OS_ == 1
    pthread_mutex_destroy(&(this->m_mutex));
#endif
}

void FE::mutex::lock() noexcept
{
    this->m_is_locked.store(true, std::memory_order_release);
#if _WINDOWS_64BIT_OS_ == 1
    WaitForSingleObject(this->m_mutex, INFINITE);
#elif _LINUX_64BIT_OS_ == 1
    pthread_mutex_lock(&(this->m_mutex));
#endif
}

void FE::mutex::unlock() noexcept
{
    this->m_is_locked.store(false, std::memory_order_release);
#if _WINDOWS_64BIT_OS_ == 1
    ReleaseMutex(this->m_mutex);
#elif _LINUX_64BIT_OS_ == 1
    pthread_mutex_unlock(&(this->m_mutex));
#endif
}

FE::var::boolean FE::mutex::try_lock() noexcept
{
#if _WINDOWS_64BIT_OS_ == 1
    if (this->m_is_locked.load(std::memory_order_acquire) == true)
    {
        return _FAILED_;
    }

    this->m_is_locked.store(true, std::memory_order_release);
    WaitForSingleObject(this->m_mutex, INFINITE);

    return _SUCCESSFUL_;

#elif _LINUX_64BIT_OS_ == 1
    this->m_is_locked.store(true, std::memory_order_release);
    return pthread_mutex_trylock(&(this->m_mutex)) == 0;
#endif
}

FE::var::boolean FE::mutex::is_locked() noexcept
{
    return this->m_is_locked.load(std::memory_order_acquire);
}




FE::timed_mutex::timed_mutex() noexcept : m_is_locked(false)
#if _WINDOWS_64BIT_OS_ == 1
, m_timed_mutex(CreateMutex(NULL, FALSE, NULL))
#endif
{
#if _LINUX_64BIT_OS_ == 1
    pthread_mutex_init(&(this->m_timed_mutex), nullptr);
#endif
}

FE::timed_mutex::~timed_mutex() noexcept
{
    FE_ASSERT(this->m_is_locked.load(std::memory_order_acquire) == true, "CRITICAL ERROR: timed mutex is still locked", _EXCEPTION_ORIGIN_);

#if _WINDOWS_64BIT_OS_ == 1
    CloseHandle(this->m_timed_mutex);
#elif _LINUX_64BIT_OS_ == 1
    pthread_mutex_destroy(&(this->m_timed_mutex));
#endif
}

void FE::timed_mutex::lock(uint32 milliseconds_p) noexcept
{
    this->m_is_locked.store(true, std::memory_order_release);
#if _WINDOWS_64BIT_OS_ == 1
    WaitForSingleObject(this->m_timed_mutex, milliseconds_p);
#elif _LINUX_64BIT_OS_ == 1
    struct timespec l_timer;
    l_timer.tv_sec = milliseconds_p / 1000;
    l_timer.tv_nsec = (milliseconds_p % 1000) * 1000000;
    pthread_mutex_timedlock(&(this->m_timed_mutex), &l_timer);
#endif
}

void FE::timed_mutex::unlock() noexcept
{
    this->m_is_locked.store(false, std::memory_order_release);
#if _WINDOWS_64BIT_OS_ == 1
    ReleaseMutex(this->m_timed_mutex);
#elif _LINUX_64BIT_OS_ == 1
    pthread_mutex_unlock(&(this->m_timed_mutex));
#endif
}

FE::var::boolean FE::timed_mutex::try_lock(uint32 milliseconds_p) noexcept
{
    if (this->m_is_locked.load(std::memory_order_acquire) == true)
    {
        return _FAILED_;
    }
#if _WINDOWS_64BIT_OS_ == 1
    this->m_is_locked.store(true, std::memory_order_release);
    WaitForSingleObject(this->m_timed_mutex, milliseconds_p);

    return _SUCCESSFUL_;

#elif _LINUX_64BIT_OS_ == 1
    struct timespec l_timer;
    l_timer.tv_sec = milliseconds_p / 1000;
    l_timer.tv_nsec = (milliseconds_p % 1000) * 1000000;
    return pthread_mutex_timedlock(&(this->m_timed_mutex), &l_timer) == 0;
#endif
}

FE::var::boolean FE::timed_mutex::is_locked() noexcept
{
    return this->m_is_locked.load(std::memory_order_acquire);
}
