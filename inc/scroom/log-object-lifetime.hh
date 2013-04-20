/*
 * Scroom Development Utilities - Stuff that's convenient while developing
 * Copyright (C) 2009-2013 Kees-Jan Dijkzeul
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License, version 2, as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _LOG_OBJECT_LIFETIME_HH
#define _LOG_OBJECT_LIFETIME_HH

namespace Scroom
{
  namespace Utilities
  {
    class bye_world
    {
    private:
      std::string message;

    private:
      static void log(const std::string& action, const std::string& message, const void* current=0, const void* old=0)
      {
        std::cout << action << " ";
        if(current)
        {
          std::cout << " (" << current;
          if(old)
            std::cout << " <- " << old;
          std::cout << ")";
        }
        std::cout << " " << message << std::endl;
      }
      
      void log(const std::string& action)
      {
        log(action, message, this);
      }

      void log_constructing()
      {
        log("Constructing");
      }

      void log_destructing()
      {
        log("Destructing ");
      }

      void log_copying(const void* old)
      {
        log("Copying     ", message, this, old);
      }

      void log_assigning(const bye_world& other)
      {
        log("Overwriting ");
        log("With        ", other.message, &other);
      }

      void log_swapping(const bye_world& other)
      {
        log("Exchanging  ");
        log("With        ", other.message, &other);
      }

    public:
      bye_world(const std::string& message)
        : message(message)
      {
        log_constructing();
      }
      
      bye_world(const bye_world& other)
      : message(other.message)
      {
        log_copying(&other);
      }
      
      bye_world& operator=(const bye_world& other)
      {
        log_assigning(other);
        message=other.message;
      }

      ~bye_world()
      {
        log_destructing();
      }

      void swap(bye_world& other)
      {
        log_swapping(other);
        message.swap(other.message);
      }

    };
  }
}

#endif
