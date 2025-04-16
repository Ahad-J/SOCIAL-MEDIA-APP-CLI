<h1 align="center">📦 CLI-Based Social Media App</h1>

<p align="center">
  <strong>A command-line social media simulation encapsulating OOP and file handling concepts in C++.</strong><br>
  <em>Focuses on inheritance, class management, and real-world interactions like posting, liking, and commenting—all through the terminal.</em>
</p>

---

## 🧩 Introduction

<b>This CLI-based Social Media App demonstrates the core principles of Object-Oriented Programming and File Handling in C++.</b>  
The design revolves around structured class management, particularly inheritance and encapsulation. The primary class manages all file operations, while child classes handle various user interactions.

---

## 🧱 Basic Framework

The structure consists of:

- 🏛️ A **Parent Class**: `MajorFunctionsUsed` – responsible for core operations like file handling.
- 👨‍👩‍👧‍👦 **Derived Classes** – implement specific user functionalities by inheriting from the parent.

---

## 🧬 Concept Exhibited

> 🔁 **Inheritance** is the core OOP concept used to manage different functionalities in an organized and extendable manner.

---

## ⚙️ Basic Functionalities

<details>
  <summary>🔸 1. Set Current User</summary>
  Ask user for their ID and set them as the active user for the session.
</details>

<details>
  <summary>🔸 2. View Home of Current User</summary>
  - See all friends' posts shared in the last 24 hours  
  - View posts from liked pages shared in the last 24 hours
</details>

<details>
  <summary>🔸 3. Like a Post</summary>
  - Input Post ID  
  - Like it (max 10 users per post)
</details>

<details>
  <summary>🔸 4. View Likes on a Post</summary>
  - Input Post ID  
  - View users who liked the post
</details>

<details>
  <summary>🔸 5. Comment on a Post</summary>
  - Input Post ID  
  - Add a comment
</details>

<details>
  <summary>🔸 6. View a Post</summary>
  - Input Post ID  
  - View full post and its comments
</details>

<details>
  <summary>🔸 7. Share a Memory</summary>
  - Input Post ID and memory text  
  - Share it
</details>

<details>
  <summary>🔸 8. View User’s Profile</summary>
  - See user name and all posts
</details>

<details>
  <summary>🔸 9. View Friend List</summary>
  - Input User ID  
  - Display list of friends
</details>

<details>
  <summary>🔸 10. View a Page</summary>
  - Input Page ID  
  - View all page posts
</details>

---

## 🖼️ Preview

<p align="center">
  <img src="https://your-image-link.com/image.png" alt="Project Screenshot" width="600"/>
</p>

---

## ✨ Features

- 💾 File-based persistent storage
- 🧠 OOP concepts like Inheritance, Encapsulation, Polymorphism
- 📥 Post, like, comment, and memory-sharing logic
- 🕵️ Role simulation (Users, Pages, Friends)
- 📂 Profile, page, and friend-list views

---

## 🚀 Working Instructions

```bash
# 1. Clone the repository
git clone https://github.com/Ahad-J/SOCIAL-MEDIA-APP-CLI.git

# 2. Open your C++ IDE or compiler

# 3. Compile the project
g++ main.cpp -o SocialApp

# 4. Run the program
./SocialApp
