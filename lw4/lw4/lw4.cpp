#include "Client.h"
#include "Canvas.h"
#include <iostream>

using namespace std;

int main()
{
	CClient client;
	client.CreatePictureDraft(cin);
	CCanvas canvas;
	client.DrawPicture(canvas);
}
