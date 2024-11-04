#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200
#define MAX_TITLE 100

// 책 구조체
typedef struct {
    char title[MAX_TITLE]; // 책 제목
} Book;

// 노래 구조체
typedef struct {
    char title[MAX_TITLE]; // 노래 제목
} Song;

// 책의 힙트리
typedef struct {
    Book heap[MAX_ELEMENT];
    int heap_size;
} BookHeapType;

// 노래 힙트리
typedef struct {
    Song heap[MAX_ELEMENT];
    int heap_size;
} SongHeapType;

// 힙 생성 및 초기화 함수
BookHeapType* create_init_Book() {
    BookHeapType* h = (BookHeapType*)malloc(sizeof(BookHeapType));
    if (h != NULL) {
        h->heap_size = 0;
    }
    return h;
}
SongHeapType* create_init_song() {
    SongHeapType* h = (SongHeapType*)malloc(sizeof(SongHeapType));
    if (h != NULL) {
        h->heap_size = 0;
    }
    return h;
}

// 문자열 비교 함수 (힙 삽입에 사용)
int compare_keys(const char* key1, const char* key2) {
    return strcmp(key1, key2);
}

// 힙 삽입 함수
void book_insert(BookHeapType* h, Book item) {
    int i = ++(h->heap_size);

    while ((i != 1) && (compare_keys(item.title, h->heap[i / 2].title) > 0)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}
void song_insert(SongHeapType* h, Song item) {
    int i = ++(h->heap_size);

    while ((i != 1) && (compare_keys(item.title, h->heap[i / 2].title) > 0)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i] = item;
}

/*
// 깊이 우선 탐색(DFS) 함수
void dfs(BookHeapType* h, int index) {
    if (index <= h->heap_size) {
        printf("제목: %s, 가중치: %d\n", h->heap[index].title, h->heap[index].weight);
        dfs(h, index * 2);
        dfs(h, index * 2 + 1);
    }
}
*/

// 중위 순회 함수
void book_inorder(BookHeapType* h, int index) {
    if (index > h->heap_size) return;

    book_inorder(h, index * 2); // 왼쪽 자식 노드
    printf("%s\n", h->heap[index].title); // 현재 노드
    book_inorder(h, index * 2 + 1); // 오른쪽 자식 노드
}
void song_inorder(SongHeapType* h, int index) {
    if (index > h->heap_size) return;

    song_inorder(h, index * 2); // 왼쪽 자식 노드
    printf("%s\n", h->heap[index].title); // 현재 노드
    song_inorder(h, index * 2 + 1); // 오른쪽 자식 노드
}

//책 제목 찾는 함수
char* book_serch(BookHeapType* h, const char* title) {
    for (int i = 1; i < h->heap_size; i++) {
        if (strcmp(h->heap[i].title, title) == 0) {
            return h->heap[i].title;
        }
    }
    return "못찾음";
}

// 파일에서 책 제목을 읽어와 힙에 삽입
void load_books_from_file(BookHeapType* h, const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0) {
        perror("파일을 열 수 없습니다");
        exit(1);
    }

    Book book;
    while (fgets(book.title, MAX_TITLE, file)) {
        book.title[strcspn(book.title, "\n")] = '\0';  // 줄바꿈 제거
        book_insert(h, book);
    }
    fclose(file);
}
void load_songs_from_file(SongHeapType* h, const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0) {
        perror("파일을 열 수 없습니다");
        exit(1);
    }

    Song song;
    while (fgets(song.title, MAX_TITLE, file)) {
        song.title[strcspn(song.title, "\n")] = '\0';  // 줄바꿈 제거
        song_insert(h, song);
    }
    fclose(file);
}

int main() {
    BookHeapType* Bheap = create_init_Book();
    SongHeapType* Sheap = create_init_song();

    load_books_from_file(Bheap, "books.txt");
    load_songs_from_file(Sheap, "songs.txt");

    //책 입력
    char BTitle[MAX_TITLE];
    printf("책 제목을 입력하세요 : ");
    gets_s(BTitle, sizeof(BTitle), "\n");
    printf("찾은 책 : %s\n\n", book_serch(Bheap, BTitle));


    printf("책 제목 (중위 순회):\n");
    book_inorder(Bheap, 1);

    printf("\n노래 제목 (중위 순회):\n");
    song_inorder(Sheap, 1);

    free(Bheap);
    free(Sheap);

    return 0;
}
