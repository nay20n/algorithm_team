#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEMENT 200
#define MAX_TITLE 100

// å ����ü
typedef struct {
    char title[MAX_TITLE]; // å ����
} Book;

// �뷡 ����ü
typedef struct {
    char title[MAX_TITLE]; // �뷡 ����
} Song;

// å�� ��Ʈ��
typedef struct {
    Book heap[MAX_ELEMENT];
    int heap_size;
} BookHeapType;

// �뷡 ��Ʈ��
typedef struct {
    Song heap[MAX_ELEMENT];
    int heap_size;
} SongHeapType;

// �� ���� �� �ʱ�ȭ �Լ�
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

// ���ڿ� �� �Լ� (�� ���Կ� ���)
int compare_keys(const char* key1, const char* key2) {
    return strcmp(key1, key2);
}

// �� ���� �Լ�
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
// ���� �켱 Ž��(DFS) �Լ�
void dfs(BookHeapType* h, int index) {
    if (index <= h->heap_size) {
        printf("����: %s, ����ġ: %d\n", h->heap[index].title, h->heap[index].weight);
        dfs(h, index * 2);
        dfs(h, index * 2 + 1);
    }
}
*/

// ���� ��ȸ �Լ�
void book_inorder(BookHeapType* h, int index) {
    if (index > h->heap_size) return;

    book_inorder(h, index * 2); // ���� �ڽ� ���
    printf("%s\n", h->heap[index].title); // ���� ���
    book_inorder(h, index * 2 + 1); // ������ �ڽ� ���
}
void song_inorder(SongHeapType* h, int index) {
    if (index > h->heap_size) return;

    song_inorder(h, index * 2); // ���� �ڽ� ���
    printf("%s\n", h->heap[index].title); // ���� ���
    song_inorder(h, index * 2 + 1); // ������ �ڽ� ���
}

//å ���� ã�� �Լ�
char* book_serch(BookHeapType* h, const char* title) {
    for (int i = 1; i < h->heap_size; i++) {
        if (strcmp(h->heap[i].title, title) == 0) {
            return h->heap[i].title;
        }
    }
    return "��ã��";
}

// ���Ͽ��� å ������ �о�� ���� ����
void load_books_from_file(BookHeapType* h, const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0) {
        perror("������ �� �� �����ϴ�");
        exit(1);
    }

    Book book;
    while (fgets(book.title, MAX_TITLE, file)) {
        book.title[strcspn(book.title, "\n")] = '\0';  // �ٹٲ� ����
        book_insert(h, book);
    }
    fclose(file);
}
void load_songs_from_file(SongHeapType* h, const char* filename) {
    FILE* file;
    errno_t err = fopen_s(&file, filename, "r");
    if (err != 0) {
        perror("������ �� �� �����ϴ�");
        exit(1);
    }

    Song song;
    while (fgets(song.title, MAX_TITLE, file)) {
        song.title[strcspn(song.title, "\n")] = '\0';  // �ٹٲ� ����
        song_insert(h, song);
    }
    fclose(file);
}

int main() {
    BookHeapType* Bheap = create_init_Book();
    SongHeapType* Sheap = create_init_song();

    load_books_from_file(Bheap, "books.txt");
    load_songs_from_file(Sheap, "songs.txt");

    //å �Է�
    char BTitle[MAX_TITLE];
    printf("å ������ �Է��ϼ��� : ");
    gets_s(BTitle, sizeof(BTitle), "\n");
    printf("ã�� å : %s\n\n", book_serch(Bheap, BTitle));


    printf("å ���� (���� ��ȸ):\n");
    book_inorder(Bheap, 1);

    printf("\n�뷡 ���� (���� ��ȸ):\n");
    song_inorder(Sheap, 1);

    free(Bheap);
    free(Sheap);

    return 0;
}
