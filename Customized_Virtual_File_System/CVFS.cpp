#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<iostream>
#include<stdio.h>
using namespace std;

#define MAXINODE 50

#define READ 1
#define WRITE 2

#define MAXFILESIZE 2048

#define REGULAR 1
#define SPECIAL 2

#define START 0
#define CURRENT 1 
#define END 2

///////////////////////////////////
//                               //
//   Structure of SuperBlock     //
//                               //
///////////////////////////////////

struct Superblock
{
   int TotalInodes;
   int FreeInodes;
};

typedef Superblock SUPERBLOCK;
typedef Superblock * PSUPERBLOCK;

///////////////////////////////////
//                               //
//   Structure of Inode          //
//                               //
///////////////////////////////////

struct Inode          
{
   char FileName[50];
   int InodeNumber;
   int FileSize;
   int FileActualSize;
   int FileType;
   char * Buffer;
   int LinkCount;
   int ReferenceCount;
   int Permission;
   struct Inode * Next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;

///////////////////////////////////
//                               //
//   Structure of FileTable      //
//                               //
///////////////////////////////////

struct FileTable
{
   int Readoffset;
   int Writeoffset;
   int Count;
   int Mode;
   PINODE ptrinode;
};

typedef struct FileTable FILETABLE;
typedef struct FileTable * PFILETABLE;

//////////////////////////////////////////////
//                                          //
//   Structure of UFDT(File Descriptor)     //
//                                          //
//////////////////////////////////////////////

struct ufdt
{
   PFILETABLE ptrfiletable;
};

typedef struct ufdt UFDT;

////////////////////////////////////////////////////////////////////////////////
/*
   Global 
*/

UFDT UFDTArr[50];
SUPERBLOCK SUPERBLOCKobj;  
PINODE Head = NULL;


/////////////////////////////////////////////////////////////////////////////////
/*
  Function to check Description of commands
  How to use command
  man : Mannual description
  usage : man command 
  example : man create
*/

void man(char * name)
{
   if(name == NULL)
   {
      return;
   }
   
   if(strcmp(name,"create") == 0)
   {
      printf("Description : Use to create new regular file\n");
      printf("Usage : create  File_Name Permission\n");
   }
   else if(strcmp(name,"read") == 0)
   {
      printf("Description : Use to read Data from regular file\n");
      printf("Usage : read File_name No_of_Bytes_To_Read\n");
   }
   else if(strcmp(name,"write") == 0)
   {
      printf("Description : Use to write Data into regular file\n");
      printf("Usage : write File_name\nAfter enter Data that you want to write\n");
   }
   else if(strcmp(name,"ls") == 0)
   {
      printf("Description : Use to list all information of files\n");
      printf("Usage : ls\n");
   }
   else if(strcmp(name,"stat") == 0)
   {
      printf("Description : Use to Display information of file\n");
      printf("Usage : stat File_name\n");
   }
   else if(strcmp(name,"fstat") == 0)
   {
      printf("Description : Use to Display information of file\n");
      printf("Usage : fstat File_Descriptor\n");
   }
   else if(strcmp(name,"truncate") == 0)
   {
      printf("Description : Use to remove data from file\n");
      printf("Usage : truncate File_name\n");
   }
   else if(strcmp(name,"open") == 0)
   {
      printf("Description : Use to open existing file\n");
      printf("Usage : open File_name Mode\n");
   }
   else if(strcmp(name,"close") == 0)
   {
      printf("Description : Use to close open file\n");
      printf("Usage : close File_name\n");
   }
   else if(strcmp(name,"closeall") == 0)
   {
      printf("Description : Use to close all opened file\n");
      printf("Usage : closeall \n");
   }
   else if(strcmp(name,"lseek") == 0)
   {
      printf("Description : Use to change file offset\n");
      printf("Usage : lseek File_name ChangeInOffset StartPoint\n");
   }
   else if(strcmp(name,"rm") == 0)
   {
      printf("Description : Use to Delete file\n");
      printf("Usage : em File_name\n");
   }
   else if(strcmp(name,"clear") == 0)
   {
      printf("Description : Use to clear console\n");
      printf("Usage : clear\n");
   }
   else
   {
      printf("ERROR : No Manual entry available....!\n");
   } 
}
//////////////////////////////////////////////////////////////////////////////////
/*
  Function to help user to understand how to use file system
*/

void DisplayHelp()
{
    printf("ls    : To list all Files\n");
    printf("clear : To clear Console\n");
    printf("open  : To open the file\n");
    printf("close : To close the file\n");
    printf("closeall : To close all opened files\n");
    printf("read  : To read the contents from file\n");
    printf("write : To Write content into file\n");
    printf("exit  : To terminate file System\n");
    printf("stat  : to Display information of files using name\n");
    printf("fstat : To Display information of files using file Descriptor\n");
    printf("truncate : To Remove all data from file\n");
    printf("rm    : To Delete File\n");
} 

//////////////////////////////////////////////////////////////////////////////////
/*
  Function to file Descriptor for the created file
*/

int GetFDFromName(char * name)
{
   int i = 0;
   
   while(i < 50)
   {
      if(UFDTArr[i].ptrfiletable != NULL)
      {
         if(strcmp((UFDTArr[i].ptrfiletable->ptrinode->FileName),name) == 0)
         {
            break;
         }
      }
      
      i++;
   }
   
   if(i == 50)
   {
      return -1;
   }
   else
   {
     return i;
   }
}

///////////////////////////////////////////////////////////////////////////////
/*
  Function To get Inode Number 
*/

PINODE Get_Inode(char * name)
{
  PINODE Temp = Head;
  int i = 0;
  
  if(name == NULL)
  {
     return NULL;
  }
  
  while(Temp != NULL)
  {
     if(strcmp(name,Temp->FileName) == 0)
     {
        break;
     }
     Temp = Temp->Next;
  }
  
  return Temp;
}

/////////////////////////////////////////////////////////////////////////////////
/*
  Function to create DILB 
*/

void CreateDILB()
{
   int i = 1;
   PINODE Newn = NULL;
   PINODE Temp = Head;
   
   while(i <= MAXINODE)
   {
       Newn = (PINODE)malloc(sizeof(INODE));
       
       Newn->LinkCount = 0;
       Newn->ReferenceCount = 0;
       Newn->FileType = 0;
       Newn->FileSize = 0;
       
       Newn->Buffer = NULL;
       Newn->Next = NULL;
       
       Newn->InodeNumber = i;
       
       if(Temp == NULL)
       {
          Head = Newn;
          Temp = Head;
       }
       else
       {
          Temp->Next = Newn;
          Temp = Temp->Next;
       }
       
       i++;
   }
   
   printf("DILB created successfully\n");
}

////////////////////////////////////////////////////////////////////////////////
/*
  Function to Initalise super block with values
  like  total Number of Inode
        total Number of free Inode
*/

void InitialiseSuperBlock()
{
   int i = 0;
   
   while(i < MAXINODE)
   {
      UFDTArr[i].ptrfiletable = NULL;
      i++;
   }
   
   SUPERBLOCKobj.TotalInodes = MAXINODE;
   SUPERBLOCKobj.FreeInodes = MAXINODE;
}

/////////////////////////////////////////////////////////////////////////////////
/*
  Function to create file
*/

int CreateFile(char * name , int Permission)
{
   int i = 0;
   PINODE Temp = Head;
   
   if((name == NULL) || (Permission == 0) || (Permission >3))
   {
      return -1;
   }
   
   if(SUPERBLOCKobj.FreeInodes == 0)
   {
      return -2;
      (SUPERBLOCKobj.FreeInodes)--;
   }   
   
   
   
   if(Get_Inode(name) != NULL) 
   {
      return -3;
   }   
      
   while(Temp != NULL)
   {
       if(Temp->FileType == 0)
       {
          break;
       }
       Temp = Temp->Next;
   }   
   
   while(i < 50)
   {
      if(UFDTArr[i].ptrfiletable  == NULL)
      {
          break;
      }
      
      i++;
   }  
   
   UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
   
   UFDTArr[i].ptrfiletable->Count = 1;
   UFDTArr[i].ptrfiletable->Mode = Permission;
   UFDTArr[i].ptrfiletable->Readoffset = 0;
   UFDTArr[i].ptrfiletable->Writeoffset = 0;
   
   UFDTArr[i].ptrfiletable->ptrinode = Temp;
   
   strcpy(UFDTArr[i].ptrfiletable->ptrinode->FileName,name);
   UFDTArr[i].ptrfiletable->ptrinode->FileType = REGULAR;
   UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount = 1;
   UFDTArr[i].ptrfiletable->ptrinode->LinkCount = 1;
   UFDTArr[i].ptrfiletable->ptrinode->FileSize = MAXFILESIZE;
   UFDTArr[i].ptrfiletable->ptrinode->FileActualSize = 0;
   UFDTArr[i].ptrfiletable->ptrinode->Permission = Permission;
   UFDTArr[i].ptrfiletable->ptrinode->Buffer = (char *)malloc(MAXFILESIZE);
   
   return i; 
   
}

////////////////////////////////////////////////////////////////////////////////////
/*
   Function to delete file 
*/
 
int rm_File(char * name)
{ 
   int fd = 0;
   
   fd = GetFDFromName(name);
   if(fd == -1)
   {
      return -1;
   }
   
   (UFDTArr[fd].ptrfiletable->ptrinode->LinkCount)--;
   
   if(UFDTArr[fd].ptrfiletable->ptrinode->LinkCount == 0)
   {
       UFDTArr[fd].ptrfiletable->ptrinode->FileType = 0;
       //free(UFDTArr[fd].ptrfiletable->ptrinode->Buffer);
       free(UFDTArr[fd].ptrfiletable);
   }
   
   UFDTArr[fd].ptrfiletable = NULL;
   (SUPERBLOCKobj.FreeInodes)++;
   
   return 0;
   
}

/////////////////////////////////////////////////////////////////////////////////
/*
  Function to read File
*/

int ReadFile(int fd , char * arr , int iSize)
{
   int Read_Size = 0;
   
   if(UFDTArr[fd].ptrfiletable == NULL)
   {
      return -1;
   }
   
   if((UFDTArr[fd].ptrfiletable->Mode != READ) && (UFDTArr[fd].ptrfiletable->Mode != READ+WRITE))
   {
      return -2;
   }
   
   
   if((UFDTArr[fd].ptrfiletable->ptrinode->Permission != READ) && (UFDTArr[fd].ptrfiletable->ptrinode->Permission != READ+WRITE))
   {
      return -2;
   }
   
    
   if(UFDTArr[fd].ptrfiletable->Readoffset == UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
   {
      return -3;
   }
   
    
   if((UFDTArr[fd].ptrfiletable->ptrinode->FileType) != REGULAR)
   {
      return -4;
   }
   
   Read_Size = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) - (UFDTArr[fd].ptrfiletable->Readoffset);
   
   if(Read_Size < iSize)
   {
      strncpy(arr,(UFDTArr[fd].ptrfiletable->ptrinode->Buffer)+(UFDTArr[fd].ptrfiletable->Readoffset),Read_Size);
      
      UFDTArr[fd].ptrfiletable->Readoffset = UFDTArr[fd].ptrfiletable->Readoffset + Read_Size;
   }
   else
   {
     
      strncpy(arr,(UFDTArr[fd].ptrfiletable->ptrinode->Buffer)+(UFDTArr[fd].ptrfiletable->Readoffset),iSize);
      
      UFDTArr[fd].ptrfiletable->Readoffset = UFDTArr[fd].ptrfiletable->Readoffset +iSize;
   }
   
   return iSize;
}

///////////////////////////////////////////////////////////////////////////////////

int WriteFile(int fd , char * arr, int iSize)
{
   if(((UFDTArr[fd].ptrfiletable->Mode) != WRITE) && ((UFDTArr[fd].ptrfiletable->Mode)!= READ+WRITE))
   {
       return -1;
   }
   
    if(((UFDTArr[fd].ptrfiletable->ptrinode->Permission) != WRITE) && ((UFDTArr[fd].ptrfiletable->ptrinode->Permission)!= READ+WRITE))
   {
       return -1;
   }
   
   if((UFDTArr[fd].ptrfiletable->Writeoffset) == MAXFILESIZE)
   {
      return -2;
   }
   
   if((UFDTArr[fd].ptrfiletable->ptrinode->FileType) != REGULAR)
   {
      return -3;
   }
   
   strncpy((UFDTArr[fd].ptrfiletable->ptrinode->Buffer) + (UFDTArr[fd].ptrfiletable->Writeoffset),arr,iSize);
   
   (UFDTArr[fd].ptrfiletable->Writeoffset) = (UFDTArr[fd].ptrfiletable->Writeoffset)+iSize;
   
   (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)+iSize;
   
   return iSize;
   
}

/////////////////////////////////////////////////////////////////////////////////

int OpenFile(char * name , int Mode)
{
   int i = 0;
   PINODE Temp = NULL;
   
   if(name == NULL|| Mode <= 0)
   {
      return -1;
   }
   
   Temp = Get_Inode(name);
   
   if(Temp->Permission < Mode)
   {
      return -3;
   } 
   
   while(i < 50)
   {
      if(UFDTArr[i].ptrfiletable == NULL)
      {
         break;
      }
      i++;
   }
   
   UFDTArr[i].ptrfiletable = (PFILETABLE)malloc(sizeof(FILETABLE));
   if(UFDTArr[i].ptrfiletable == NULL)
   {
      return -1;
   }
   
   UFDTArr[i].ptrfiletable->Count = 1;
   UFDTArr[i].ptrfiletable->Mode = Mode;
   
   if(Mode == READ + WRITE)
   {
      UFDTArr[i].ptrfiletable->Readoffset = 0;
      UFDTArr[i].ptrfiletable->Writeoffset = 0;
   }
   else if(Mode == READ)
   {
      UFDTArr[i].ptrfiletable->Readoffset = 0;
   }
   else if(Mode == WRITE)
   {
      UFDTArr[i].ptrfiletable->Writeoffset = 0;
   }
   UFDTArr[i].ptrfiletable->ptrinode = Temp;
   (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)++;
   
   return i;
   
}

////////////////////////////////////////////////////////////////////////////

void CloseFileByName(int fd)
{
   UFDTArr[fd].ptrfiletable->Readoffset = 0;
   UFDTArr[fd].ptrfiletable->Writeoffset = 0;
   (UFDTArr[fd].ptrfiletable->ptrinode->ReferenceCount)--;
}

/////////////////////////////////////////////////////////////////////////

int CloseFileByName(char * name)
{
   int i = 0;
   i = GetFDFromName(name);
   
   if(i == -1)
   {
      return -1;
   }
   
   UFDTArr[i].ptrfiletable->Readoffset = 0;
   UFDTArr[i].ptrfiletable->Writeoffset = 0;
   (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;
   
   return 0;
}

//////////////////////////////////////////////////////////////////////////////

void CloseAllFile()
{
   int i = 0;
   
   while(i < 50)
   {
      if(UFDTArr[i].ptrfiletable != NULL)
      {
          UFDTArr[i].ptrfiletable->Readoffset = 0;
          UFDTArr[i].ptrfiletable->Writeoffset = 0;
          (UFDTArr[i].ptrfiletable->ptrinode->ReferenceCount)--;
          break;
      }
      i++;
   } 
}

///////////////////////////////////////////////////////////////////////////////

int LseekFile(int fd , int Size , int From)
{
   if((fd < 0) || (From > 2))
   {
      return -1;
   }
   
   if((UFDTArr[fd].ptrfiletable->Mode == READ) || (UFDTArr[fd].ptrfiletable->Mode == READ + WRITE))
   {
      if(From == CURRENT)
      {
         if(((UFDTArr[fd].ptrfiletable->Readoffset)+Size) > UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize)
         {
            return -1;
         }
         
         if((UFDTArr[fd].ptrfiletable->Readoffset)+Size < 0)
         {
            return -1;
         }
         
         (UFDTArr[fd].ptrfiletable->Readoffset) = (UFDTArr[fd].ptrfiletable->Readoffset)+Size;
      }
      else if(From == START)
      {
         if(Size >(UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
         {
            return -1;
         }
         
         if(Size < 0)
         {
            return -1;
         }
         
         (UFDTArr[fd].ptrfiletable->Readoffset) = Size;
      }
      else if(From == END)
      {
         if((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + Size > MAXFILESIZE)
         {
            return -1;
         }
         
         if(((UFDTArr[fd].ptrfiletable->Readoffset) + Size) < 0)
         {
            return -1;
         }
         
         (UFDTArr[fd].ptrfiletable->Readoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + Size;
      }
   }
   else if(UFDTArr[fd].ptrfiletable->Mode == WRITE)
   {
      if(From == CURRENT)
      {
          if(((UFDTArr[fd].ptrfiletable->Writeoffset) + Size) > MAXFILESIZE)
          {
             return -1;
          } 
          
          if(((UFDTArr[fd].ptrfiletable->Writeoffset) + Size) < 0)
          {
              return -1;
          }
          
          if(((UFDTArr[fd].ptrfiletable->Writeoffset) + Size) > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
          {
             (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = (UFDTArr[fd].ptrfiletable->Writeoffset)+Size;
          }
          
          (UFDTArr[fd].ptrfiletable->Writeoffset) = (UFDTArr[fd].ptrfiletable->Writeoffset)+Size;
      }
      else if(From == START)
      {
         if(Size > MAXFILESIZE)
         {
            return -1;
         }
         if(Size < 0)
         {
            return -1;         
         }
         if(Size > (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize))
         {
            (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) = Size;
         }
         
         (UFDTArr[fd].ptrfiletable->Writeoffset) = Size;
      }
      else if(From == END)
      {
         if((UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + Size > MAXFILESIZE)
         {
            return -1;
         }
         
         if(((UFDTArr[fd].ptrfiletable->Writeoffset) + Size) < 0)
         {
            return -1;
         }
         
         (UFDTArr[fd].ptrfiletable->Writeoffset) = (UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize) + Size;
      }
      
   }
   return 0;
}

///////////////////////////////////////////////////////////////////////////////////

void ls_File()
{
   int i = 0;
   PINODE Temp = Head;
   
   if(SUPERBLOCKobj.FreeInodes == MAXINODE)
   {
       printf("ERROR : There are no Files\n");
       return;
   }
   
   printf("-------------------------------------------------------\n");
   printf("FileName\tInode Number\tFile Size\tLink Count\n");
   printf("-------------------------------------------------------\n");
   
   while(Temp != NULL)
   { 
      if(Temp->FileType != 0)
      {
         printf("%s\t\t%d\t\t%d\t\t%d\n",Temp->FileName,Temp->InodeNumber,Temp->FileActualSize,Temp->LinkCount);
      }
      Temp = Temp->Next;
   } 
   
   printf("-------------------------------------------------------\n");
}

///////////////////////////////////////////////////////////////////////////////////

int fstat_file(int fd)
{
   PINODE Temp = Head;
   int i = 0;
   
   if(fd < 0)
   {
      return -1;
   }
   
   if(UFDTArr[fd].ptrfiletable == NULL)
   { 
      return -2;
   } 
   
   Temp = UFDTArr[fd].ptrfiletable->ptrinode;
   
   printf("\n--------Statistical Information about file-----------\n");
   printf("File Name : %s\n",Temp->FileName);
   printf("Inode Number : %d\n",Temp->InodeNumber);
   printf("File Size : %d\n",Temp->FileSize);
   printf("Actual File Size : %d\n",Temp->FileActualSize);
   printf("Link Count : %d\n",Temp->LinkCount);
   printf("Reference Count : %d\n",Temp->ReferenceCount);
   
   if(Temp->Permission == 1)
   {
      printf("File Permission : Read Only\n");
   }
   else if(Temp->Permission == 2)
   {
      printf("File Permission : Write Only\n");
   }
   else if(Temp->Permission == 3)
   {
       printf("File Permission : Read and Write\n");
   }
   printf("-----------------------------------------------------\n");
   
   return 0;
}

///////////////////////////////////////////////////////////////////////////////

int stat_file(char * name)
{
   PINODE Temp = Head;
   int i = 0;
   
   if(name == NULL)
   {
      return -1;
   }
   
   while(Temp != NULL)
   {
       if(strcmp(name,Temp->FileName) == 0)
       { 
          break;
       } 
       Temp = Temp->Next;
   }
   
   if(Temp == NULL)
   {
      return -2;
   }
   
   printf("\n--------Statistical Information about file-----------\n");
   printf("File Name : %s\n",Temp->FileName);
   printf("Inode Number : %d\n",Temp->InodeNumber);
   printf("File Size : %d\n",Temp->FileSize);
   printf("Actual File Size : %d\n",Temp->FileActualSize);
   printf("Link Count : %d\n",Temp->LinkCount);
   printf("Reference Count : %d\n",Temp->ReferenceCount);
   
    if(Temp->Permission == 1)
   {
      printf("File Permission : Read Only\n");
   }
   else if(Temp->Permission == 2)
   {
      printf("File Permission : Write Only\n");
   }
   else if(Temp->Permission == 3)
   {
       printf("File Permission : Read and Write\n");
   }
   printf("-----------------------------------------------------\n");
   
   return 0;
}

/////////////////////////////////////////////////////////////////////////////

int truncate_file(char * name)
{
   int fd = GetFDFromName(name);
   
   if(fd == -1)
   {
      return -1;
   }
   
   memset(UFDTArr[fd].ptrfiletable->ptrinode->Buffer,0,1024);
   UFDTArr[fd].ptrfiletable->Readoffset = 0;
   UFDTArr[fd].ptrfiletable->Writeoffset = 0;
   UFDTArr[fd].ptrfiletable->ptrinode->FileActualSize = 0;
   
   return 0;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
  char * ptr = NULL;
  int Ret = 0;
  int fd = 0;
  int Count = 0;
  
  char command[4][80] , str[80], arr[1024];
  
  InitialiseSuperBlock();
  CreateDILB();
  
  while(1)
  {
     fflush(stdin);
     strcpy(str,"");
     
     printf("\n Rohit's VFS 👉️ ");
     
     fgets(str,80,stdin); //scanf("%[^'\n']s",str);
     
     Count = sscanf(str,"%s %s %s %s",command[0],command[1],command[2],command[3]);
     
     if(Count == 1)
     {
        if(strcmp(command[0] , "ls") == 0)
        {
            ls_File();
        }
        else if(strcmp(command[0],"closeall") == 0)
        {
            CloseAllFile();
            printf("All Files closed Successfully\n");
            continue;
        }
        else if(strcmp(command[0],"clear") == 0)
        {
            system("clear");
            continue;
        }
        else if(strcmp(command[0],"help") == 0)
        {
            DisplayHelp();
            continue;
        }
        else if(strcmp(command[0],"exit") == 0)
        {
            
            printf("Terminating the Rohit's Virtual File System\n");
            break;
        }
        else 
        {
            printf("ERROR : Command Not Found!!!");
            continue;
        }
        
     }
     else if(Count == 2)
     {
        if(strcmp(command[0],"stat") == 0)
        {
           Ret = stat_file(command[1]);
           if(Ret == -1)
           {
              printf("ERROR : Incorrect Parameters\n");
           }
           if(Ret == -2)
           {
              printf("ERROR : There is No Such File\n");
              continue;
           }
        }   
        else if(strcmp(command[0],"fstat") == 0)
        {
           Ret = fstat_file(atoi(command[1]));
           if(Ret == -1)
           {
              printf("ERROR : Incorrect Parameters\n");
           }
           if(Ret == -2)
           {
              printf("ERROR : There is No Such File\n");
              continue;
           }
        }
        else if(strcmp(command[0],"close") == 0)
        {
           Ret = CloseFileByName(command[1]);
           if(Ret == -1)
           {
              printf("ERROR : There is No Such File\n");
              continue;
           }
        }
        else if(strcmp(command[0],"rm") == 0)
        {
           Ret = rm_File(command[1]);
           if(Ret == -1)
           {
              printf("ERROR : There is No Such File\n");
              continue;
           }
        }
        else if(strcmp(command[0],"man") == 0)
        {
           man(command[1]);
        }         
        else if(strcmp(command[0],"write") == 0)
        {
           fd = GetFDFromName(command[1]);
           if(fd == -1)
           {
              printf("ERROR : Incorrect Parameters\n");
              continue;
           }
           printf("Enter Data : \n");
           scanf("%[^'\n']s",arr);
           
           Ret = strlen(arr);
           if(Ret == 0)
           {
              printf("ERROR : Incorrect Parameters\n");
              continue;
           }
           
           Ret = WriteFile(fd,arr,Ret);
           if(Ret == -1)
           {
              printf("ERROR : Permission Denied\n");
           }
           if(Ret == -2)
           {
             printf("ERROR : There is no sufficient memory to write\n");
           }
           if(Ret == -3)
           {
              printf("ERROR : It is Not Regular File\n");
           }
        }  
        else if(strcmp(command[0],"truncate") == 0)
        {
           Ret = truncate_file(command[1]);
           if(Ret == -1)
           {
              printf("ERROR : Incorrect Parameter\n");
              continue;
           }
           else
           {
               printf("ERROR : Command Not Found\n");
               continue;
           }
        }   
     }
     else if(Count == 3)
     {
        if(strcmp(command[0],"create") == 0)
        { 
            Ret = CreateFile(command[1],atoi(command[2]));
            if(Ret >= 0)
            {
               printf("File is created successfully with file Descriptor %d\n",Ret);
            }
            if(Ret == -1)
            {
              printf("ERROR : Incorrect Parameter\n");
            }
            if(Ret == -2)
            {
               printf("ERROR : There is No Inode\n");
            }
            if(Ret == -3)
            {
               printf("ERROR : Permission Denied\n");
            }
            continue;
        }  
        
        else if(strcmp(command[0],"open") == 0)
        {
           Ret = OpenFile(command[1],atoi(command[2]));
           
           if(Ret >= 0)
           {
             printf("File is successfully opened with file Descriptor %d\n",Ret);
           }
           if(Ret == -1)
           {
              printf("ERROR : Incorrect parameter\n");
           }
           if(Ret == -2)
           {
              printf("ERROR : FIle Not Opened\n");
           }
           if(Ret == -3)
           {
              printf("ERROR : Permission Denied\n");
           }
           continue;
        } 
        else if((command[0],"read") == 0)
        {
           fd = GetFDFromName(command[1]);
           
           if(fd == -1)
           {
             printf("ERROR : Incorrect Parameter\n");
             continue;
           }
           ptr = (char * )malloc(sizeof(atoi(command[2])) + 1);
           
           if(ptr == NULL)
           {
              printf("ERROR : Memory allocation failure\n");
              continue;
           }
           
           Ret = ReadFile(fd,ptr,atoi(command[2]));
           
           if(Ret == -1)
           {
              printf("ERROR : File not existing\n");
           }
           if(Ret == -2)
           {
              printf("ERROR : Permission Denied\n");
           }
           if(Ret == -3)
           {
              printf("ERROR : Reached at end of file\n");
           }
           if(Ret == -4)
           {
              printf("ERROR : It is not regular file\n");
           }
           
           if(Ret > 0)
           {
               write(2,ptr,Ret);
           }
           continue;
        }
        else
        {
           printf("\nERROR : Command Not Found\n");
           continue;
        }
        
     } 
     else if(Count == 4)
     {
         if(strcmp(command[0],"lseek") == 0)
         {
            fd = GetFDFromName(command[1]);
            if(fd == -1)
            {
               printf("ERROR : Incorrect Parameter\n");
               continue;
            }
            
            Ret = LseekFile(fd,atoi(command[2]),atoi(command[3]));
            
            if(Ret == -1)
            {
               printf("ERROR : Unable to perform lseek\n");
            }
         }
         else
         {
             printf("\nERROR : Command Not Found!!!\n");
             continue;
         }
     } 
     else
     {
        printf("\nERROR : Command Not Found!!!\n");
        continue;
     }   
   }  
  return 0;
}
