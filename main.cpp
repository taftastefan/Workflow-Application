#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <regex>
#include <sstream>
using namespace std;
class Operation
{
public:
float add(float a, float b)
    {
        return a + b;
    }


    float sub(float a,float b)
    {
        return a - b;
    }


    float mul(float a, float b)
    {
        return a * b;
    }

    float div(float a, float b)
    {
        if (b == 0)
        {
            cout << "Division By Zero" <<
                     endl;
            return 0;
        }
        else
        {
            return a / b;
        }
    }

    float mini(float a, float b)
    {
        if(a<b)
        return a;
        return b;
    }

    float maxi(float a, float b)
    {
        if(a>b)
        return a;
        return b;
    }
};
class Step
{
private:
    string name;
public:
    virtual ~Step() = default;
    void set_name(string x)
    {
        this->name = x;
    }
    string get_name() const
    {
        return this->name;
    }
    virtual void execute() {}
    virtual void set_param() {}
    virtual string file()
    {

    }
};
class TitleStep: public Step
{
private:
    string title, subtitle;
public:
    TitleStep(string a,string b)
    {
        title = a;
        subtitle = b;
    }
    TitleStep()
    {
        title="";
        subtitle="";
    }
    void set_param() override
    { string t,s;
        cout<<"Please enter the title: ";
        cin>>t;
        cout<<"Please enter the subtitle: ";
        cin>>s;
        title = t;
        subtitle = s;
    }
    void execute() override
    {
        cout<<"Step "<<get_name()<<" with the title: "<<title<<" and the subtitle: "<<subtitle<<endl;;
    }
    string file()
    {
        string a="Step "+get_name()+" with the title "+title+" and subtitle: "+subtitle;
        return a;
    }
};
class TextStep:public Step
{
private:
    string title, copyy;
public:
    void set_param() override
    {
        string t, c;
        cout<<"Please enter the title of the text: ";
        cin>>t;
        cout<<"Please enter the copy: ";
        cin>>c;
        title = t;
        copyy = c;
    }
    void execute() override
    {
        cout<<"Step "<<get_name()<<" with the title: "<<title<<" and the copy: "<<copyy<<endl;
    }
     string file()
    {
        string a="Step "+get_name()+" with the title "+title+" and copy: "+ copyy;
        return a;
    }
};
class TextInput:public Step
{
private:
    string description, input;
public:
    void set_param() override
    {
        string d;
        cout<<"Please enter the description of the text: ";
        cin>>d;
        description = d;
    }
    void execute() override
    {   string i;
        cout<<description<<":";
        cin>>i;
        input = i;
        cout<<"Step "<<get_name()<<" with the description: "<<description<<" and the text input: "<<input<<endl;
    }
      string file()
    {
        string a="Step "+get_name()+" with the description "+description+" and text input "+ input;
        return a;
    }
};
class NumberInput:public Step
{
private:
    int number;
    string description;
public:
    void set_param()
    {
        string d;
        cout<<"Please enter the description of the text: ";
        cin>>d;
        description = d;

    }
    void execute()
    {   int n;
        cout<<description<<":";
        cin>>n;
        number = n;
        cout<<"Step "<<get_name()<<" with the description: "<<description<<" and the number input: "<<number<<endl;
    }
    float get_val()
    {
        return number;
    }
     string file()
    {
        string a="Step "+get_name()+" with the description "+description+" and number input "+ to_string(number);
        return a;
    }

};
class Calculus:public Step
{
private:
    vector<int> v;
    string operation;
    float result;
    vector<Step*>x;
public:
    Calculus(vector <Step*> b)
    {
        x = b;
    }
    void set_param()
    {


    }
    void execute()
    {
         string op;
        vector<int> steps;
        int number;
        cout<<"Please enter the number of steps: ";
       do {cin>>number;}while(number<0);

        for (int i=0;i<number;i++)
        {   int step;
            cout<<"Please enter step no "<<i+1<<": ";
            do{cin>>step;
            if(step>=x.size()||x[step]->get_name()!="NumberInput")
            cout<<"Step is not valid. Please enter NumberInput step"<<endl;
                }while(step>=x.size()||x[step]->get_name()!="NumberInput");
            steps.push_back(step);
        }
        cout<<"Please enter the operation:";
        do {
    cin >> op;
} while (op != "+" && op != "-" && op != "/" && op != "*" && op != "min" && op != "max");
        operation=op;
        v=steps;
    int n = v.size();
    float numberInputs[n];

    for (int i = 0; i < n; i++) {
        int step = v[i];
        NumberInput *numStep = dynamic_cast<NumberInput*>(x[step]);
        numberInputs[i] = numStep->get_val();
    }

    Operation c;
    if(operation=="+")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.add(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }

    if(operation=="-")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.sub(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }
    if(operation=="*")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.mul(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }

        if(operation=="/")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.div(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }

            if(operation=="min")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.mini(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }

        if(operation=="max")
    {   float re;
        re = numberInputs[0];
        for (int j=1;j<v.size();j++)
        re=c.maxi(numberInputs[j],re);
       result=re;
       cout<<re<<endl;
    }
}
    string file()
    {
        string a="Step "+get_name()+" with steps ";
        for (int i=0;i<v.size();i++)
            {
                a+=to_string(v[i]);
                a+=" ";
            }
        a+="and operation ";
        a+=operation;
        return a;
    }
};
class TextFile:public Step
{
private:
    string description, file_name;
public:
    void set_param() override
    {
        string d;
        cout<<"Please enter the description of the text file: ";
        cin>>d;
        description = d;
    }
    void execute() override
    {    string fn;
         cout<<description<<":";
         cin>>fn;
         file_name=fn;
        cout<<"Step "<<get_name()<<" with the text file name "<<file_name<<" and the description "<<description<<" was added"<<endl;
    }
    string file()
    {
        string a="Step "+get_name()+" with the description "+ description+" and txt file name "+file_name;
        return a;
    }
    string get_txt_name()
    {
        return file_name;
    }
};
class CsvFile:public Step
{
private:
    string description, file_name;
public:
    void set_param() override
    {
        string d;
        cout<<"Please enter the description of the CSV file: ";
        cin>>d;
        description = d;
    }
    void execute() override
    {    string fn;
         cout<<description<<":";
         cin>>fn;
         file_name=fn;
         cout<<"Step "<<get_name()<<" with the CSV file name "<<file_name<<" and the description "<<description<<" was added"<<endl;
    }
    string file()
    {
        string a="Step "+get_name()+" with the description "+ description+" and CSV file name "+file_name;
        return a;
    }
    string get_csv_name()
    {
        return file_name;
    }
};
class Output:public Step
{
private:
    vector<int> s;
    string file_name, title, description;
    vector<Step*> x;
public:
    Output(vector<Step*> b)
    {
        x =b;
    }
    void set_param() override
    {
        string fn, t, d;
        cout<<"Please enter the file name: ";
        cin>>fn;
        cout<<"Please enter the title: ";
        cin>>t;
        cout<<"Please enter the description: ";
        cin>>d;
        file_name = fn;
        title = t;
        description = d;
    }
    void execute() override
    {    vector <int> steps;
        int a;
        cout<<"Please enter the number of steps: ";
        cin>>a;
        for(int i=0;i<a;i++)
        {
            int step;
            cout<<"Please enter step number "<<i+1<<" ";
            do{
                cin>>step;
                if(step>=x.size())
                    cout<<"Step is not valid"<<endl;
            }while(step>=x.size());
            steps.push_back(step);
        }
        s=steps;
        ofstream f;
        f.open(file_name,ios::app);
        f<<title<<endl<<description<<endl;
        for(int i=0;i<s.size();i++)
            f<<x[s[i]]->file()<<endl;
        f<<"***";
        f.close();
    }
    string file()
    {
        string a="Step "+get_name()+" wrote steps:";
        for(int i=0;i<s.size();i++)
        {
            a=a+to_string(s[i]);
            a=a+" ";
        }
        return a;
    }
};
class Display: public Step
{
private:
    int step;
    vector<Step*> x;
public:
    Display(vector<Step*> b)
    {
        x = b;
    }
    void set_param()
    {

    }
    void execute()
    {
    int s;
    cout<<"Please enter the file step to open: ";
    do{
        cin>>s;
        cout<<x[s]->get_name()<<endl;
        if(s>=x.size() || (x[s]->get_name()!="CSVFile" && x[s]->get_name()!="TextFile"))
            cout<<"Invalid file step. Please enter another step: ";
    }while(s>=x.size() || (x[s]->get_name()!="CSVFile" && x[s]->get_name()!="TextFile"));

        step = s;
    if(x[step]->get_name() == "CSVFile")
    {
        CsvFile *CsvStep = dynamic_cast<CsvFile*>(x[step]);
        ifstream inputfile(CsvStep->get_csv_name());
        string a;
        while(getline(inputfile,a))
        {
            cout<<a<<endl;
        }
    }
    else {
        TextFile *TextStep = dynamic_cast<TextFile*>(x[step]);
        ifstream inputfile(TextStep->get_txt_name());
        string a;
        while(getline(inputfile,a))
        {
            cout<<a<<endl;
        }
    }
    }
};
class End:public Step
{
public:
    void execute()
    {
        cout<<"End step";
    }
    string file()
    {
        return "EndStep";
    }
};
class Builder
{
private:
    vector<Step*> steps;
public:
    void add_Step(Step* step)
    {
        steps.push_back(step);
    }
    void execute_Step() const
    {
        for(const auto& step : steps){
            step->execute();
        }
    }
    Step* get_Step(int i)
    {
        return steps[i];
    }
    vector<Step*> returnare()
    {
        return steps;
    }
};
void CreateFlowinterface();
void interface();
void ExistingFlow();
void DeleteFlow();
void CreateFlow();
void Test();
void interface()
{
    int option;

    cout << "  1. Build a flow using existing predefined steps\n";
    cout << "  2. See a flow that I have created              \n";
    cout << "  3. Delete a flow                               \n";
    cout << "  4. Test a matrix                                                  \n";
    cout << "  5. Exit                                                        \n";
    cout << "  Your option is ___                                       \n";
    cout << "                                                           \n";
    cout << "\n";

    cin >> option;

    switch (option)
    {

    case 1:
        CreateFlowinterface();
        break;
    case 2:
        ExistingFlow();
        break;
    case 3:
        DeleteFlow();
        break;
    case 4:
        Test();
        break;
    case 5:
        return;
    }
}
void ExistingFlow()
{

   ifstream file("Output.txt");

    if (!file.is_open()) {
        cout << "Unable to open the file." << endl;

    }


    string searchString;
    cout << "Enter the search string: ";
    cin>>searchString;

    string patternString = searchString + "[\\s\\S]*?\\*\\*\\*";
    regex pattern(patternString);
    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());


    sregex_iterator iter(content.begin(), content.end(), pattern);
    sregex_iterator end;

    for (; iter != end; ++iter) {
        cout << "Found: " << iter->str() << endl;
    }
    file.close();
}
void CreateFlowinterface()
{
    int option;
    cout << "   1.	TITLE step                               \n";
    cout << "   2.	TEXT step                                       \n";
    cout << "   3.	TEXT INPUT step                      \n";
    cout << "   4.	NUMBER INPUT step                  \n";
    cout << "   5.	CALCULUS step                                 \n";
    cout << "   6.	DISPLAY steps                                                       \n";
    cout << "   7.	TEXT FILE input step                                  \n";
    cout << "   8.	CSV FILE input step                                   \n";
    cout << "   9. OUTPUT step  \n";
    cout << "  10.END step                                                                         \n";
    cout << "                                                                                      \n";
    cout << "   Do you want to create a new flow?  (yes-1/no-2)                                    \n";
    cout << "                                                                                      \n";
    cout << "\n";

    cin >> option;

    switch (option)
    {
    case 1:
        CreateFlow();
        break;
    case 2:
        interface();
        break;
    }
}
void CreateFlow()
{
    Builder builder;
    vector<Step*> la;
    vector<Step*> la1;
    vector<Step*> la2;
    TitleStep *a = new TitleStep;
    TextStep *b = new TextStep;
    TextInput *c = new TextInput;
    NumberInput *d = new NumberInput;
    TextFile *g = new TextFile;
    CsvFile *h = new CsvFile;
    End *j = new End;
    a->set_param();
    a->set_name("TitleStep");
    builder.add_Step(a);
    builder.get_Step(0)->execute();

    b->set_param();
    b->set_name("TextStep");
    builder.add_Step(b);
    builder.get_Step(1)->execute();

    c->set_param();
    c->set_name("TextInput");
    builder.add_Step(c);
    builder.get_Step(2)->execute();

    d->set_param();
    d->set_name("NumberInput");
    builder.add_Step(d);
    builder.get_Step(3)->execute();
    la2 = builder.returnare();
    Calculus *e = new Calculus(la2);
    e->set_param();
    e->set_name("CalculusStep");
    builder.add_Step(e);
    builder.get_Step(4)->execute();

    g->set_param();
    g->set_name("TextFile");
    builder.add_Step(g);
    builder.get_Step(5)->execute();

    h->set_param();
    h->set_name("CSVFile");
    builder.add_Step(h);
    builder.get_Step(6)->execute();

    la1 = builder.returnare();
    Display *f = new Display(la1);
    f->set_param();
    f->set_name("DisplayStep");
    builder.add_Step(f);
    builder.get_Step(7)->execute();

    la = builder.returnare();
    Output *i = new Output(la);
    i->set_param();
    i->set_name("OutputStep");
    builder.add_Step(i);
    builder.get_Step(8)->execute();

    j->set_param();
    j->set_name("EndStep");
    builder.add_Step(j);
    builder.get_Step(9)->execute();
}
void DeleteFlow()
{
    ifstream inputFile("Output.txt");

    if (!inputFile.is_open()) {
       cout << "Unable to open the input file." << endl;
    }
    string content((istreambuf_iterator<char>(inputFile)),istreambuf_iterator<char>());
    inputFile.close();
    string searchString;
    cout << "Enter the search string: ";
    cin >> searchString;
    string escapedSearchString =regex_replace(searchString, regex("([.+?^=!:${}()|[\]/\\])"), "\$1");
    string patternString = escapedSearchString + "[\\s\\S]*?\\*\\*\\*";
    regex pattern(patternString);
    ofstream tempFile("temp.txt");

    if (!tempFile.is_open()) {
        cout << "Unable to create the temporary file." << endl;
    }
    sregex_iterator iter(content.begin(), content.end(), pattern);
    sregex_iterator end;

    size_t lastPos = 0;

    for (; iter != end; ++iter) {
        size_t matchPos = iter->position();
        tempFile << content.substr(lastPos, matchPos - lastPos);
        lastPos = matchPos + iter->length();
    }

    tempFile << content.substr(lastPos);
    tempFile.close();

    remove("Output.txt");
    rename("temp.txt", "Output.txt");

    cout << "Lines matching the pattern have been deleted." << endl;
}
void Test()
{   Builder build;
    vector<vector<string>> Test={
        {"Title:salut,buna,","NumberInput:numar,3,","TextFile:descriere,CSV.csv,","DisplayStep:5,"}
    };
    for(int i=0;i<Test[0].size();i++)
    {
        string word;
        istringstream iss(Test[0][i]);
        getline(iss,word,':');
        if(word=="Title")
        {
            string t,subt;
            getline(iss,word,',');
            t = word;
            getline(iss,word,',');
            subt = word;
            Step *x=new TitleStep(t,subt);
            x->set_name("TitleStep");
            build.add_Step(x);
            x->execute();
        }
    }
}
int main()
{  interface();
    return 0;
}

