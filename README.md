# ✈️ Airline Booking System (C Language)

A terminal-based airline booking application written in C. It supports **Admin** and **User** functionality and allows users to register, 
book flights, make payments, and view details about their most expensive paid trip.

---

## 📋 Features

### Admin
- Secure login
- Set and update flight prices (airport taxes + base cost)
- Must initialize the system before users can register

### User
- Register with name, address, and password
- Auto-generated username based on surname
- Login and view personal information
- Modify address details
- Book up to 3 flights to predefined cities
- View cost per flight
- Make payments
- See most expensive paid flight

---

## 🔐 Admin Access

| Username   | Password |
|------------|----------|
| `airadmin` | `Air123` |

> The admin must log in and enter city prices before users can access the system.

---

## 🧭 How to Use

1. **Run the program** — Choose between Admin or User
2. **Admin sets prices** — Required before any user activity
3. **User registers** — Auto-generated username will be shown
4. **User logs in** — Can then:
   - View or edit their info
   - Book up to 3 flights
   - Make payments
   - View most expensive trip

---

## ⚠️ Notes

- This program **does not save data** — everything resets when closed.
- Designed for **educational purposes**.
- A maximum of **20 users** can register in one session.
- Each user can book **up to 3 flights**.
- Destination cities are limited to **10 predefined** options (e.g., `ROM`, `MAD`, `LON`, `BER`, `AMS`, `NYW`, `BEI`, `CHI`, `SYD`, etc.).

